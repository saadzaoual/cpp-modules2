#include <iostream>
#include <vector>
#include <cstdlib>
#include "Span.hpp"

int main(void)
{
    // ===== 1. Subject's classic example =====
    std::cout << "===== 1. classic example =====" << std::endl;
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << "shortest: " << sp.shortestSpan() << " (expected 2)" << std::endl;
    std::cout << "longest:  " << sp.longestSpan() << " (expected 14)" << std::endl;

    // ===== 2. addNumber on a full Span throws =====
    std::cout << std::endl << "===== 2. overfill via addNumber =====" << std::endl;
    try
    {
        sp.addNumber(1000);
        std::cout << "ERROR: should have thrown" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "caught: " << e.what() << std::endl;
    }

    // ===== 3. span methods on empty / single-element Span throw =====
    std::cout << std::endl << "===== 3. not enough numbers =====" << std::endl;
    Span emptySpan(5);
    try
    {
        emptySpan.shortestSpan();
        std::cout << "ERROR: should have thrown" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "caught (empty): " << e.what() << std::endl;
    }

    Span oneSpan(5);
    oneSpan.addNumber(42);
    try
    {
        oneSpan.longestSpan();
        std::cout << "ERROR: should have thrown" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "caught (one element): " << e.what() << std::endl;
    }

    // ===== 4. range-based addNumber =====
    std::cout << std::endl << "===== 4. range add =====" << std::endl;
    std::vector<int> source;
    source.push_back(1);
    source.push_back(50);
    source.push_back(100);

    Span sp2(10);
    sp2.addNumber(source.begin(), source.end());
    std::cout << "sp2 shortest: " << sp2.shortestSpan() << " (expected 49)" << std::endl;
    std::cout << "sp2 longest:  " << sp2.longestSpan() << " (expected 99)" << std::endl;

    // ===== 5. range add that would overflow throws, and doesn't partially insert =====
    std::cout << std::endl << "===== 5. range add overflow (no partial insert) =====" << std::endl;
    Span sp3(2);
    std::vector<int> bigSource;
    bigSource.push_back(1);
    bigSource.push_back(2);
    bigSource.push_back(3);
    try
    {
        sp3.addNumber(bigSource.begin(), bigSource.end());
        std::cout << "ERROR: should have thrown" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "caught: " << e.what() << std::endl;
    }
    // confirm nothing was partially inserted: sp3 should still be able to hold 2 numbers
    sp3.addNumber(10);
    sp3.addNumber(20);
    std::cout << "sp3 after clean add: shortest = " << sp3.shortestSpan() << std::endl;

    // ===== 6. OCF deep-copy check =====
    std::cout << std::endl << "===== 6. copy constructor / assignment =====" << std::endl;
    Span original(5);
    original.addNumber(1);
    original.addNumber(2);
    original.addNumber(3);

    Span copyCtor(original);           // copy constructor
    Span copyAssign(1);
    copyAssign = original;             // copy assignment

    copyCtor.addNumber(100);           // modify the copy only
    std::cout << "original still has 3 elements? shortest/longest still work: "
              << original.shortestSpan() << " / " << original.longestSpan() << std::endl;
    std::cout << "copyCtor now has 4 elements, longest: " << copyCtor.longestSpan() << std::endl;
    std::cout << "copyAssign longest (should equal original's): "
              << copyAssign.longestSpan() << std::endl;

    // ===== 7. large-scale test (subject requires handling many numbers efficiently) =====
    std::cout << std::endl << "===== 7. large scale: 10,000 numbers =====" << std::endl;
    Span bigSpan(10000);
    std::vector<int> bigNums;
    std::srand(42);
    for (int i = 0; i < 10000; i++)
        bigNums.push_back(std::rand() % 1000000);
    bigSpan.addNumber(bigNums.begin(), bigNums.end());
    std::cout << "shortest: " << bigSpan.shortestSpan() << std::endl;
    std::cout << "longest:  " << bigSpan.longestSpan() << std::endl;

    return 0;
}