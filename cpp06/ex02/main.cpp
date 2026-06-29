#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void)
{
    int r = std::rand() % 3;

    if (r == 0)
        return new A();
    else if (r == 1)
        return new B();
    else
        return new C();
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void identify(Base& p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    }
    catch (const std::exception&)
    {
        try
        {
            (void)dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
        }
        catch (const std::exception&)
        {
            (void)dynamic_cast<C&>(p);
            std::cout << "C" << std::endl;
        }
    }
}

int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    for (int i = 0; i < 6; i++)
    {
        Base* obj = generate();

        std::cout << "--- test " << i << " ---" << std::endl;
        std::cout << "by pointer:   ";
        identify(obj);                  // pointer version
        std::cout << "by reference: ";
        identify(*obj);                 // reference version (dereference the pointer)

        delete obj;                     // caller owns the heap memory
    }
    return 0;
}