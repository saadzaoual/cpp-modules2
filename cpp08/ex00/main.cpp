#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main(void)
{
    std::vector<int> v;
    for (int i = 1; i <= 5; i++)
        v.push_back(i * 10);

    std::cout << "=== vector {10,20,30,40,50} ===" << std::endl;
    try
    {
        std::vector<int>::iterator it = easyfind(v, 30);
        std::cout << "found: " << *it << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "=== searching for 99 (absent) ===" << std::endl;
    try
    {
        easyfind(v, 99);
        std::cout << "found (unexpected!)" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "caught: " << e.what() << std::endl;
    }

    std::list<int> l;
    l.push_back(100);
    l.push_back(200);
    l.push_back(300);

    std::cout << std::endl << "=== list {100,200,300} ===" << std::endl;
    try
    {
        std::list<int>::iterator it = easyfind(l, 200);
        std::cout << "found: " << *it << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    std::deque<int> d;
    d.push_back(7);
    d.push_back(8);
    d.push_back(9);

    std::cout << std::endl << "=== deque {7,8,9} ===" << std::endl;
    try
    {
        std::deque<int>::iterator it = easyfind(d, 8);
        std::cout << "found: " << *it << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "=== modify via returned iterator ===" << std::endl;
    try
    {
        std::vector<int>::iterator it = easyfind(v, 30);
        *it = 999;
        std::cout << "changed 30 to " << v[2] << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    return 0;
}