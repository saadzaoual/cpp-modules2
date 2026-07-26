#include "BitcoinExchange.hpp"
#include <cstdlib>

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

const char *BitcoinExchange::CouldNotOpenFileException::what() const throw()
{
    return ("Error: could not open file.");
}

const char *BitcoinExchange::InvalidDatabaseFormatException::what() const throw()
{
    return ("Error: invalid database format, expected 'date,exchange_rate'");
}

BitcoinExchange::InvalidDateException::InvalidDateException(std::string const &line)
    : _msg("Error: bad input => " + line)
{
}

BitcoinExchange::InvalidDateException::~InvalidDateException() throw()
{
}

const char *BitcoinExchange::InvalidDateException::what() const throw()
{
    return (_msg.c_str());
}

const char *BitcoinExchange::InvalidValueException::what() const throw()
{
    return ("Error: not a positive number.");
}

const char *BitcoinExchange::ValueTooLargeException::what() const throw()
{
    return ("Error: too large a number.");
}

std::map<std::string, double> const &BitcoinExchange::getDatabase() const
{
    return (_database);
}

void BitcoinExchange::_loadDatabase(std::string const &fileName)
{
    std::ifstream file(fileName.c_str());
    if (!file.is_open())
        throw CouldNotOpenFileException();

    std::string line;
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

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return (false);

    if (month == 2)
    {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28))
            return (false);
    }
    return (true);
}

double BitcoinExchange::_parseValue(std::string const &value) const
{
    if (value.empty())
        throw InvalidValueException();

    // reject nan / inf before the stream accepts them
    for (std::string::size_type i = 0; i < value.size(); i++)
    {
        if (isalpha(value[i]))
            throw InvalidValueException();
    }

    double              parsed;
    std::istringstream  stream(value);

    if (!(stream >> parsed))
        throw InvalidValueException();

    std::string leftover;
    if (stream >> leftover)
        throw InvalidValueException();

    if (parsed < 0)
        throw InvalidValueException();
    if (parsed > 1000)
        throw ValueTooLargeException();

    return (parsed);
}

void BitcoinExchange::_processLine(std::string const &line)
{
    std::string::size_type sep = line.find('|');

    if (sep == std::string::npos)
        throw InvalidDateException(line);

    std::string date  = line.substr(0, sep);
    std::string value = line.substr(sep + 1);

    while (!date.empty() && (date[date.size() - 1] == ' ' || date[date.size() - 1] == '\t'))
        date.erase(date.size() - 1);
    while (!value.empty() && (value[0] == ' ' || value[0] == '\t'))
        value.erase(0, 1);

    if (!_isValidDate(date))
        throw InvalidDateException(date);

    double amount = _parseValue(value);

    std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

    if (it == _database.end() || it->first != date)
    {
        if (it == _database.begin())
            throw InvalidDateException(date);
        --it;
    }

    double result = amount * it->second;
    std::cout << date << " => " << amount << " = " << result << std::endl;
}

void BitcoinExchange::execute(char const *fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
        throw CouldNotOpenFileException();

    std::string line;

    if (std::getline(file, line))
    {
        if (line != "date | value")
        {
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