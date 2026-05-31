#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    std::cout << "===== TEST 1: Valid form creation =====" << std::endl;
    try
    {
        Form taxes("TaxReturn", 50, 25);
        std::cout << taxes << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 2: Invalid sign grade (too high) =====" << std::endl;
    try
    {
        Form bad("BadForm", 0, 50);
        std::cout << bad << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 3: Invalid sign grade (negative) =====" << std::endl;
    try
    {
        Form bad("BadForm", -10, 50);
        std::cout << bad << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 4: Invalid execute grade (too low) =====" << std::endl;
    try
    {
        Form bad("BadForm", 50, 151);
        std::cout << bad << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 5: Invalid execute grade (huge number) =====" << std::endl;
    try
    {
        Form bad("BadForm", 50, 9999);
        std::cout << bad << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 6: Bureaucrat with sufficient grade signs =====" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 10);
        Form taxes("TaxReturn", 50, 25);

        std::cout << "Before: " << taxes << std::endl;
        boss.signForm(taxes);
        std::cout << "After:  " << taxes << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 7: Bureaucrat with insufficient grade fails =====" << std::endl;
    try
    {
        Bureaucrat intern("Intern", 130);
        Form contract("Contract", 50, 25);

        std::cout << "Before: " << contract << std::endl;
        intern.signForm(contract);
        std::cout << "After:  " << contract << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 8: Exact grade match (boundary) =====" << std::endl;
    try
    {
        Bureaucrat clerk("Clerk", 50);
        Form taxes("TaxReturn", 50, 25);   

        std::cout << "Before: " << taxes << std::endl;
        clerk.signForm(taxes);              
        std::cout << "After:  " << taxes << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 9: Signing an already-signed form =====" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 10);
        Bureaucrat manager("Manager", 20);
        Form taxes("TaxReturn", 50, 25);

        boss.signForm(taxes);       
        std::cout << taxes << std::endl;
        manager.signForm(taxes);    
        std::cout << taxes << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 10: Calling beSigned() directly (no try/catch in signForm) =====" << std::endl;
    try
    {
        Bureaucrat intern("Intern", 130);
        Form topSecret("TopSecret", 5, 1);

        topSecret.beSigned(intern);   
        std::cout << "This should not print" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught from beSigned directly: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 11: Copy constructor and assignment =====" << std::endl;
    try
    {
        Form original("Original", 30, 10);
        Bureaucrat boss("Boss", 5);
        boss.signForm(original);   

        Form copy(original);       
        std::cout << "Original: " << original << std::endl;
        std::cout << "Copy:     " << copy << std::endl;

        Form other("Other", 100, 50);   
        std::cout << "Before assignment, other: " << other << std::endl;
        other = original;       
        std::cout << "After  assignment, other: " << other << std::endl;
        
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 12: Operator<< chaining =====" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 1);
        Form contract("Contract", 50, 25);

        std::cout << "Meet " << alice << " and the form " << contract << "." << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== END OF TESTS =====" << std::endl;
    return (0);
}