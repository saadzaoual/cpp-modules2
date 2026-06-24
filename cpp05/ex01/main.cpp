#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    try
    {
        Form contract("Contract", 50, 25);
        std::cout << contract << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "---" << std::endl;

    try
    {
        Form bad("BadHigh", 0, 25);
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try
    {
        Form bad("BadLow", 50, 151);
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << "---" << std::endl;

    {
        Bureaucrat boss("Boss", 10);
        Form taxes("TaxReturn", 50, 25);
        boss.signForm(taxes);
        std::cout << taxes << std::endl;
    }

    std::cout << "---" << std::endl;

    {
        Bureaucrat intern("Intern", 130);
        Form secret("TopSecret", 5, 1);
        intern.signForm(secret);
        std::cout << secret << std::endl;
    }

    std::cout << "---" << std::endl;

    {
        Bureaucrat exact("Exact", 50);
        Form form("Boundary", 50, 50);
        exact.signForm(form);
    }

    std::cout << "---" << std::endl;

    try
    {
        Bureaucrat weak("Weak", 100);
        Form form("DirectForm", 40, 20);
        form.beSigned(weak);
    }
    catch (std::exception &e)
    {
        std::cout << "Caught directly: " << e.what() << std::endl;
    }

    return 0;
}