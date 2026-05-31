#include "Bureaucrat.hpp"

int main(void)
{
    std::cout << "===== TEST 1: Valid construction =====" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 42);
        std::cout << alice << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 2: Grade too high (0) =====" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 0);
        std::cout << bob << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 3: Grade too high (negative) =====" << std::endl;
    try
    {
        Bureaucrat carol("Carol", -5);
        std::cout << carol << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 4: Grade too low (151) =====" << std::endl;
    try
    {
        Bureaucrat dave("Dave", 151);
        std::cout << dave << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 5: Grade too low (very high number) =====" << std::endl;
    try
    {
        Bureaucrat eve("Eve", 9999);
        std::cout << eve << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 6: Increment at upper boundary (grade 1) =====" << std::endl;
    try
    {
        Bureaucrat frank("Frank", 1);
        std::cout << frank << std::endl;
        frank.incrementGrade();   // should throw
        std::cout << frank << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 7: Decrement at lower boundary (grade 150) =====" << std::endl;
    try
    {
        Bureaucrat grace("Grace", 150);
        std::cout << grace << std::endl;
        grace.decrementGrade();   // should throw
        std::cout << grace << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 8: Successful increment and decrement =====" << std::endl;
    try
    {
        Bureaucrat henry("Henry", 50);
        std::cout << henry << std::endl;

        henry.incrementGrade();   // 50 -> 49
        std::cout << "After increment: " << henry << std::endl;

        henry.decrementGrade();   // 49 -> 50
        std::cout << "After decrement: " << henry << std::endl;

        henry.decrementGrade();   // 50 -> 51
        std::cout << "After decrement: " << henry << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 9: Copy constructor =====" << std::endl;
    try
    {
        Bureaucrat original("Original", 75);
        Bureaucrat copy(original);
        std::cout << "Original: " << original << std::endl;
        std::cout << "Copy:     " << copy << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 10: Assignment operator =====" << std::endl;
    try
    {
        Bureaucrat a("Aaa", 30);
        Bureaucrat b("Bbb", 100);
        std::cout << "Before: " << a << " | " << b << std::endl;
        a = b;
        std::cout << "After:  " << a << " | " << b << std::endl;
        // Note: name stays "Aaa" because _name is const, only grade is copied
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 11: Operator<< chaining =====" << std::endl;
    try
    {
        Bureaucrat x("Xavier", 10);
        Bureaucrat y("Yara", 20);
        std::cout << "Meet " << x << " and " << y << "!" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== END OF TESTS =====" << std::endl;
    return (0);
}