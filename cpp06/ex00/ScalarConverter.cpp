#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& copy)
{
    (void)copy;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& copy)
{
    (void)copy;
    return (*this);
}

ScalarConverter::~ScalarConverter()
{
}

static bool isPseudoDouble(const std::string& s)
{
    return (s == "nan" || s == "+inf" || s == "-inf" || s == "inf");
}

static bool isPseudoFloat(const std::string& s)
{
    return (s == "nanf" || s == "+inff" || s == "-inff" || s == "inff");
}

static bool isCharLiteral(const std::string& s)
{
    return (s.length() == 1 && !std::isdigit(s[0]));
}

static bool isIntLiteral(const std::string& s)
{
    size_t i = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;
    if (i == s.length())
        return false;
    for (; i < s.length(); i++)
        if (!std::isdigit(s[i]))
            return false;
    return true;
}

static bool isFloatLiteral(const std::string& s)
{
    if (isPseudoFloat(s))
        return true;
    if (s.length() < 2 || s[s.length() - 1] != 'f')
        return false;

    std::string num = s.substr(0, s.length() - 1);
    size_t i = 0;
    bool dot = false;

    if (num[i] == '+' || num[i] == '-')
        i++;
    if (i == num.length())
        return false;
    for (; i < num.length(); i++)
    {
        if (num[i] == '.')
        {
            if (dot)
                return false;
            dot = true;
        }
        else if (!std::isdigit(num[i]))
            return false;
    }
    return dot;
}

static bool isDoubleLiteral(const std::string& s)
{
    if (isPseudoDouble(s))
        return true;

    size_t i = 0;
    bool dot = false;

    if (s[i] == '+' || s[i] == '-')
        i++;
    if (i == s.length())
        return false;
    for (; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            if (dot)
                return false;
            dot = true;
        }
        else if (!std::isdigit(s[i]))
            return false;
    }
    return dot;
}

static void printChar(double d)
{
    std::cout << "char: ";
    if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
        std::cout << "impossible";
    else if (!std::isprint(static_cast<int>(d)))
        std::cout << "Non displayable";
    else
        std::cout << "'" << static_cast<char>(d) << "'";
    std::cout << std::endl;
}

static void printInt(double d)
{
    std::cout << "int: ";
    if (std::isnan(d) || std::isinf(d) ||
        d < std::numeric_limits<int>::min() ||
        d > std::numeric_limits<int>::max())
        std::cout << "impossible";
    else
        std::cout << static_cast<int>(d);
    std::cout << std::endl;
}

static void printFloat(double d)
{
    std::cout << "float: ";
    float f = static_cast<float>(d);
    if (!std::isnan(f) && !std::isinf(f) && f == static_cast<int>(f))
        std::cout << static_cast<int>(f) << ".0f";
    else
        std::cout << f << "f";
    std::cout << std::endl;
}

static void printDouble(double d)
{
    std::cout << "double: ";
    if (!std::isnan(d) && !std::isinf(d) && d == static_cast<int>(d))
        std::cout << static_cast<int>(d) << ".0";
    else
        std::cout << d;
    std::cout << std::endl;
}

static void printAll(double d)
{
    printChar(d);
    printInt(d);
    printFloat(d);
    printDouble(d);
}

static void printInvalid(const std::string& literal)
{
    (void)literal;
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

static void convertFromChar(const std::string& literal)
{
    double d = static_cast<double>(literal[0]);
    printAll(d);
}

static void convertFromInt(const std::string& literal)
{
    double d = std::atof(literal.c_str());
    printAll(d);
}

static void convertFromFloat(const std::string& literal)
{
    std::string num = literal.substr(0, literal.length() - 1);
    double d = std::atof(num.c_str());
    printAll(d);
}

static void convertFromDouble(const std::string& literal)
{
    double d = std::atof(literal.c_str());
    printAll(d);
}

void ScalarConverter::convert(const std::string& literal)
{
    if (isCharLiteral(literal))
        convertFromChar(literal);
    else if (isIntLiteral(literal))
        convertFromInt(literal);
    else if (isFloatLiteral(literal))
        convertFromFloat(literal);
    else if (isDoubleLiteral(literal))
        convertFromDouble(literal);
    else
        printInvalid(literal);
}