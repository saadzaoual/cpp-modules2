#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter
{
    public:
        enum LiteralType
        {
            CHAR,
            INT,
            FLOAT,
            DOUBLE,
            PSEUDO_FLOAT,
            PSEUDO_DOUBLE,
            INVALID
        };

    private:
        // Canonical members are private to prevent instantiation.
        ScalarConverter();
        ScalarConverter(const ScalarConverter& copy);
        ScalarConverter& operator=(const ScalarConverter& other);
        ~ScalarConverter();

        // Internal helpers
        static LiteralType detectType(const std::string& literal);
        static double      parseValue(const std::string& literal, LiteralType type);

        static void displayChar(double value, LiteralType type);
        static void displayInt(double value, LiteralType type);
        static void displayFloat(double value, LiteralType type);
        static void displayDouble(double value, LiteralType type);

    public:
        // The only entry point — convert a literal and display all four types.
        static void convert(const std::string& literal);
};

#endif