#include "iter.hpp"
#include <iostream>
#include <string>

void printInt(const int& n)
{
    std::cout << n << std::endl;
}

void printString(const std::string& s)
{
    std::cout << s << std::endl;
}

int main()
{
    int numbers[] = {1, 2, 3, 4, 5};
    std::string words[] = {"Hello", "World", "CPP07"};

    iter(numbers, 5, printInt);

    std::cout << "-----" << std::endl;

    iter(words, 3, printString);

    return 0;
}