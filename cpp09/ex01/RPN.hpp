#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include <cctype>

class rpn
{
    private:
        std::stack<int> _numbers;

        int     CalculationResult(int a, int b, char o);

    public:
        rpn();
        rpn(const rpn &copy);
        rpn &operator=(const rpn &other);
        ~rpn();

        void    ReadInput(std::string input);
};

#endif