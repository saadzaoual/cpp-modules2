#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>

ScalarConverter::ScalarConverter() { }

ScalarConverter::ScalarConverter(const ScalarConverter&) { }

ScalarConverter& ScalarConverter::operator=(const ScalarConverter&)
{
    return (*this);
}

ScalarConverter::~ScalarConverter() { }

ScalarConverter::LiteralType ScalarConverter::detectType(const std::string& literal)
{
    // Step 1: pseudo-literals
    if (literal == "nanf" || literal == "+inff" || literal == "-inff")
        return (PSEUDO_FLOAT);
    if (literal == "nan" || literal == "+inf" || literal == "-inf")
        return (PSEUDO_DOUBLE);

    // Step 2: empty string
    if (literal.length() == 0)
        return (INVALID);

    // Step 3: single non-digit character
    if (literal.length() == 1 && !std::isdigit(literal[0]))
        return (CHAR);

    // Step 4: walk through characters
    size_t i = 0;
    if (literal[0] == '+' || literal[0] == '-')
        i = 1;
    if (i >= literal.length())
        return (INVALID);

    int dotCount = 0;
    int fCount = 0;

    for (; i < literal.length(); i++)
    {
        if (std::isdigit(literal[i]))
            continue;
        else if (literal[i] == '.')
            dotCount++;
        else if (literal[i] == 'f' && i == literal.length() - 1)
            fCount++;
        else
            return (INVALID);
    }

    // Step 5: classify
    if (dotCount == 0 && fCount == 0)
        return (INT);
    if (dotCount == 1 && fCount == 1)
        return (FLOAT);
    if (dotCount == 1 && fCount == 0)
        return (DOUBLE);

    return (INVALID);
}
// need to understand parsevalue
double ScalarConverter::parseValue(const std::string& literal, LiteralType type)
{
    if (type == PSEUDO_DOUBLE || type == PSEUDO_FLOAT)
    {
        if (literal == "nan" || literal == "nanf")
            return (std::numeric_limits<double>::quiet_NaN());
        if (literal == "+inf" || literal == "+inff")
            return (std::numeric_limits<double>::infinity());
        if (literal == "-inf" || literal == "-inff")
            return (-std::numeric_limits<double>::infinity());
    }

    if (type == CHAR)
        return (static_cast<double>(literal[0]));

    if (type == INT || type == FLOAT || type == DOUBLE)
        return (std::atof(literal.c_str()));

    return (0);
}

void ScalarConverter::displayChar(double value, LiteralType type)
{
    if (type == PSEUDO_FLOAT || type == PSEUDO_DOUBLE)
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }

    if (value < 0 || value > 127)
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }

    char c = static_cast<char>(value);
    if (!std::isprint(c))
    {
        std::cout << "char: Non displayable" << std::endl;
        return;
    }

    std::cout << "char: '" << c << "'" << std::endl;
}

void ScalarConverter::displayInt(double value, LiteralType type)
{
    if (type == PSEUDO_FLOAT || type == PSEUDO_DOUBLE)
    {
        std::cout << "int: impossible" << std::endl;
        return;
    }

    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
    {
        std::cout << "int: impossible" << std::endl;
        return;
    }

    std::cout << "int: " << static_cast<int>(value) << std::endl;
}

void ScalarConverter::displayFloat(double value, LiteralType type)
{
    if (type == PSEUDO_FLOAT || type == PSEUDO_DOUBLE)
    {
        if (std::isnan(value))
            std::cout << "float: nanf" << std::endl;
        else if (value > 0)
            std::cout << "float: +inff" << std::endl;
        else
            std::cout << "float: -inff" << std::endl;
        return;
    }

    if (value < -std::numeric_limits<float>::max() || value > std::numeric_limits<float>::max())
    {
        std::cout << "float: impossible" << std::endl;
        return;
    }

    float f = static_cast<float>(value);
    std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
}

void ScalarConverter::displayDouble(double value, LiteralType type)
{
    if (type == PSEUDO_FLOAT || type == PSEUDO_DOUBLE)
    {
        if (std::isnan(value))
            std::cout << "double: nan" << std::endl;
        else if (value > 0)
            std::cout << "double: +inf" << std::endl;
        else
            std::cout << "double: -inf" << std::endl;
        return;
    }

    std::cout << "double: " << std::fixed << std::setprecision(1) << value << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
    LiteralType type = detectType(literal);

    if (type == INVALID)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    double value = parseValue(literal, type);

    displayChar(value, type);
    displayInt(value, type);
    displayFloat(value, type);
    displayDouble(value, type);
}