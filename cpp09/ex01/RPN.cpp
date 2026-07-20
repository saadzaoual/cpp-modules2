#include "RPN.hpp"

rpn::rpn()
{
}

rpn::rpn(const rpn &copy)
{
    this->operator=(copy);
}

rpn &rpn::operator=(const rpn &other)
{
    if (this != &other)
        _numbers = other._numbers;
    return (*this);
}

rpn::~rpn()
{
}


int rpn::CalculationResult(int a, int b, char o)
{
    switch (o)
    {
        case '+':
            return (a + b);
        case '-':
            return (a - b);
        case '*':
            return (a * b);
        case '/':
        {
            if (b == 0)
                throw std::invalid_argument("Error: division by zero");
            return (a / b);
        }
    }
    return (0);
}

void rpn::ReadInput(std::string input)
{
    std::string operators = "+-*/";

    for (size_t i = 0; i < input.length(); i++)
    {
        if (isspace(input[i]))
            continue;

        if (isdigit(input[i]))
        {
            _numbers.push(input[i] - '0');
        }
        else if (operators.find(input[i]) != std::string::npos)
        {
            if (_numbers.size() < 2)
                throw std::invalid_argument("Error");

            int b = _numbers.top();
            _numbers.pop();
            int a = _numbers.top();
            _numbers.pop();

            _numbers.push(CalculationResult(a, b, input[i]));
        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }

    if (_numbers.size() != 1)
        throw std::invalid_argument("Error");

    std::cout << _numbers.top() << std::endl;
}