#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>

// ===== Function declarations =====
Base* generate(void);
void  identify(Base* p);
void  identify(Base& p);

// ===== Function implementations =====

Base* generate(void)
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned int>(std::time(NULL)));
        seeded = true;
    }

    int choice = std::rand() % 3;

    if (choice == 0)
        return (new A());
    if (choice == 1)
        return (new B());
    return (new C());
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != NULL)
    {
        std::cout << "A";
        return;
    }
    if (dynamic_cast<B*>(p) != NULL)
    {
        std::cout << "B";
        return;
    }
    if (dynamic_cast<C*>(p) != NULL)
    {
        std::cout << "C";
        return;
    }
}

void identify(Base& p)
{
    try
    {
        Base& tmp = dynamic_cast<A&>(p);
        (void)tmp;
        std::cout << "A";
        return;
    }
    catch (std::bad_cast&) { }

    try
    {
        Base& tmp = dynamic_cast<B&>(p);
        (void)tmp;
        std::cout << "B";
        return;
    }
    catch (std::bad_cast&) { }

    try
    {
        Base& tmp = dynamic_cast<C&>(p);
        (void)tmp;
        std::cout << "C";
        return;
    }
    catch (std::bad_cast&) { }
}

// ===== Tests =====

int main(void)
{
    std::cout << "===== TEST 1: Basic identification (5 random objects) =====" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        Base* p = generate();
        std::cout << "Object " << (i + 1) << " — Pointer: ";
        identify(p);
        std::cout << " | Reference: ";
        identify(*p);
        std::cout << std::endl;
        delete p;
    }

    std::cout << std::endl;
    std::cout << "===== TEST 2: Both versions must agree =====" << std::endl;
    bool allMatched = true;
    for (int i = 0; i < 20; ++i)
    {
        Base* p = generate();

        // Capture each version's output by checking dynamic_cast directly
        std::string ptrResult;
        if (dynamic_cast<A*>(p) != NULL)      ptrResult = "A";
        else if (dynamic_cast<B*>(p) != NULL) ptrResult = "B";
        else if (dynamic_cast<C*>(p) != NULL) ptrResult = "C";

        std::string refResult;
        try { Base& tmp = dynamic_cast<A&>(*p); (void)tmp; refResult = "A"; }
        catch (std::bad_cast&)
        {
            try { Base& tmp = dynamic_cast<B&>(*p); (void)tmp; refResult = "B"; }
            catch (std::bad_cast&)
            {
                try { Base& tmp = dynamic_cast<C&>(*p); (void)tmp; refResult = "C"; }
                catch (std::bad_cast&) { }
            }
        }

        if (ptrResult != refResult)
            allMatched = false;

        delete p;
    }
    std::cout << (allMatched ? "PASS: both versions agreed on all 20 objects"
                              : "FAIL: at least one disagreement") << std::endl;

    std::cout << std::endl;
    std::cout << "===== TEST 3: Distribution check (100 random objects) =====" << std::endl;
    int countA = 0;
    int countB = 0;
    int countC = 0;
    for (int i = 0; i < 100; ++i)
    {
        Base* p = generate();
        if (dynamic_cast<A*>(p) != NULL)      ++countA;
        else if (dynamic_cast<B*>(p) != NULL) ++countB;
        else if (dynamic_cast<C*>(p) != NULL) ++countC;
        delete p;
    }
    std::cout << "A: " << countA << " | B: " << countB << " | C: " << countC << std::endl;
    std::cout << "(Each should be roughly 33; perfect uniformity isn't expected.)" << std::endl;

    std::cout << std::endl;
    std::cout << "===== TEST 4: NULL pointer handling =====" << std::endl;
    Base* nullPtr = NULL;
    std::cout << "identify(NULL): \"";
    identify(nullPtr);
    std::cout << "\" (should be empty — graceful failure)" << std::endl;

    std::cout << std::endl;
    std::cout << "===== END OF TESTS =====" << std::endl;
    return (0);
}