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

/*
** a = the FIRST operand  (pushed first, sits deeper in the stack)
** b = the SECOND operand (pushed last, popped first)
** For "a b -" we must compute a - b, NOT b - a.
*/
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
            // need at least two operands on the stack
            if (_numbers.size() < 2)
                throw std::invalid_argument("Error");

            int b = _numbers.top();   // SECOND operand (pushed last)
            _numbers.pop();
            int a = _numbers.top();   // FIRST operand (pushed first)
            _numbers.pop();

            _numbers.push(CalculationResult(a, b, input[i]));
        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }

    // at the end there must be EXACTLY one value left
    if (_numbers.size() != 1)
        throw std::invalid_argument("Error");

    std::cout << _numbers.top() << std::endl;
}