#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
 
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <limits>
 
class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& copy);
        ScalarConverter& operator=(const ScalarConverter& other);
        ~ScalarConverter();
 
    public:
        static void convert(const std::string& literal);
};
 
#endif