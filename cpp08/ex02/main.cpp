#include <iostream>
#include <stack>
#include <list>
#include "MutantStack.hpp"

int main(void)
{
    // ===== 1. Basic stack behavior still works =====
    std::cout << "===== 1. basic stack ops =====" << std::endl;
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << "top: " << mstack.top() << " (expected 17)" << std::endl;
    mstack.pop();
    std::cout << "top after pop: " << mstack.top() << " (expected 5)" << std::endl;
    std::cout << "size: " << mstack.size() << " (expected 1)" << std::endl;

    // ===== 2. Iteration works (the whole point) =====
    std::cout << std::endl << "===== 2. iteration =====" << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    std::cout << "contents via iterator: ";
    while (it != ite)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    // ===== 3. Const iterator =====
    std::cout << std::endl << "===== 3. const_iterator =====" << std::endl;
    const MutantStack<int> constStack(mstack);
    std::cout << "const contents: ";
    for (MutantStack<int>::const_iterator cit = constStack.begin(); cit != constStack.end(); ++cit)
        std::cout << *cit << " ";
    std::cout << std::endl;

    // ===== 4. Reverse iterator =====
    std::cout << std::endl << "===== 4. reverse iterator =====" << std::endl;
    std::cout << "reversed: ";
    for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << std::endl;

    // ===== 5. Equivalence test: swap MutantStack for std::list =====
    std::cout << std::endl << "===== 5. equivalence with std::list =====" << std::endl;
    {
        std::list<int> lst(mstack.begin(), mstack.end());
        std::cout << "as list:      ";
        for (std::list<int>::iterator lit = lst.begin(); lit != lst.end(); ++lit)
            std::cout << *lit << " ";
        std::cout << std::endl;

        std::cout << "as MutantStack: ";
        for (MutantStack<int>::iterator sit = mstack.begin(); sit != mstack.end(); ++sit)
            std::cout << *sit << " ";
        std::cout << std::endl;
        std::cout << "(both lines should match)" << std::endl;
    }

    // ===== 6. Works with other types (template check) =====
    std::cout << std::endl << "===== 6. MutantStack<std::string> =====" << std::endl;
    MutantStack<std::string> sstack;
    sstack.push("hello");
    sstack.push("mutant");
    sstack.push("stack");
    for (MutantStack<std::string>::iterator sit = sstack.begin(); sit != sstack.end(); ++sit)
        std::cout << *sit << " ";
    std::cout << std::endl;

    return 0;
}