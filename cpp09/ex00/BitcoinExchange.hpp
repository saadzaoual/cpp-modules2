#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <fstream>
#include <sstream>
#include <cctype>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _database;

        void    _loadDatabase(std::string const &fileName);
        bool    _isValidDate(std::string const &date) const;
        double  _parseValue(std::string const &value) const;
        void    _processLine(std::string const &line);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &copy);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        std::map<std::string, double> const &getDatabase() const;
        void    execute(char const *fileName);

        class CouldNotOpenFileException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class InvalidDatabaseFormatException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class InvalidDateException : public std::exception
        {
            private:
                std::string _msg;

            public:
                InvalidDateException(std::string const &line);
                virtual ~InvalidDateException() throw();

                virtual const char *what() const throw();
        };

        class InvalidValueException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class ValueTooLargeException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
};

#endif