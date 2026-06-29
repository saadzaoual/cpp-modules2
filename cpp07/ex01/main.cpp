#include <iostream>
#include <string>
#include "iter.hpp"

//functions that READ elements 
template <typename T>
void printElem(const T& x)
{
    std::cout << x << " ";
}

//functions that MODIFY elements (non-const reference)
template <typename T>
void addOne(T& x)
{
    x += 1;
}

template <typename T>
void doubleIt(T& x)
{
    x *= 2;
}

int main(void)
{
    std::cout << "===== int array =====" << std::endl;
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    std::cout << "original:   ";
    iter(arr, len, printElem<int>);
    std::cout << std::endl;

    iter(arr, len, addOne<int>);
    std::cout << "after +1:   ";
    iter(arr, len, printElem<int>);
    std::cout << std::endl;

    iter(arr, len, doubleIt<int>);
    std::cout << "after x2:   ";
    iter(arr, len, printElem<int>);
    std::cout << std::endl;

    std::cout << std::endl << "===== double array =====" << std::endl;
    double darr[] = {1.5, 2.5, 3.5};
    std::cout << "original:   ";
    iter(darr, 3, printElem<double>);
    std::cout << std::endl;

    iter(darr, 3, doubleIt<double>);
    std::cout << "after x2:   ";
    iter(darr, 3, printElem<double>);
    std::cout << std::endl;

    std::cout << std::endl << "===== string array =====" << std::endl;
    std::string words[] = {"templates", "are", "generic"};
    std::cout << "strings:    ";
    iter(words, 3, printElem<std::string>);
    std::cout << std::endl;

    std::cout << std::endl << "===== char array =====" << std::endl;
    char letters[] = {'a', 'b', 'c', 'd'};
    std::cout << "chars:      ";
    iter(letters, 4, printElem<char>);
    std::cout << std::endl;

    return 0;
}