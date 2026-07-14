#include "BitcoinExchange.hpp"
#include <cstdlib>

/* ========================= OCF ========================= */

BitcoinExchange::BitcoinExchange()
{
    _loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    *this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _database = other._database;
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

/* ========================= getter ========================= */

std::map<std::string, double> const &BitcoinExchange::getDatabase() const
{
    return (_database);
}

/* ========================= load the database ========================= */

void BitcoinExchange::_loadDatabase(std::string const &fileName)
{
    std::ifstream file(fileName.c_str());

    if (!file.is_open())
        throw CouldNotOpenFileException();

    std::string line;

    // read + check the header line
    if (!std::getline(file, line) || line != "date,exchange_rate")
        throw InvalidDatabaseFormatException();

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::string         date;
        std::string         rateStr;
        std::istringstream  ss(line);

        if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr))
            throw InvalidDatabaseFormatException();

        double              rate;
        std::istringstream  rateStream(rateStr);

        if (!(rateStream >> rate))
            throw InvalidDatabaseFormatException();

        _database[date] = rate;
    }
    file.close();
}

/* ========================= date validation ========================= */

bool BitcoinExchange::_isValidDate(std::string const &date) const
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return (false);

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (isdigit(date[i]) == 0)
            return (false);
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return (false);
    if (day < 1 || day > 31)
        return (false);

    // months with only 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return (false);

    // february, with leap-year handling
    if (month == 2)
    {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28))
            return (false);
    }
    return (true);
}

/* ========================= value validation ========================= */

double BitcoinExchange::_parseValue(std::string const &value) const
{
    if (value.empty())
        throw InvalidValueException();

    double              parsed;
    std::istringstream  stream(value);

    if (!(stream >> parsed))
        throw InvalidValueException();

    // reject trailing garbage, e.g. "1.5abc"
    std::string leftover;
    if (stream >> leftover)
        throw InvalidValueException();

    if (parsed < 0)
        throw InvalidValueException();
    if (parsed > 1000)
        throw ValueTooLargeException();

    return (parsed);
}

/* ========================= process one input line ========================= */

void BitcoinExchange::_processLine(std::string const &line)
{
    std::string::size_type sep = line.find('|');

    if (sep == std::string::npos)
        throw InvalidDateException();

    std::string date  = line.substr(0, sep);
    std::string value = line.substr(sep + 1);

    // trim trailing space from date, leading space from value
    while (!date.empty() && (date[date.size() - 1] == ' ' || date[date.size() - 1] == '\t'))
        date.erase(date.size() - 1);
    while (!value.empty() && (value[0] == ' ' || value[0] == '\t'))
        value.erase(0, 1);

    if (!_isValidDate(date))
        throw InvalidDateException();

    double amount = _parseValue(value);   // throws on bad/too-large value

    // find the exchange rate: exact match, else the closest EARLIER date
    std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

    if (it == _database.end() || it->first != date)
    {
        if (it == _database.begin())
            throw InvalidDateException();   // date is before any record we have
        --it;                                // step back to the closest earlier date
    }

    double result = amount * it->second;
    std::cout << date << " => " << amount << " = " << result << std::endl;
}

/* ========================= entry point ========================= */

void BitcoinExchange::execute(char const *fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
        throw CouldNotOpenFileException();

    std::string line;

    // skip the header line if present
    if (std::getline(file, line))
    {
        if (line != "date | value")
        {
            // no header — treat this first line as data
            try
            {
                _processLine(line);
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        try
        {
            _processLine(line);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    file.close();
}