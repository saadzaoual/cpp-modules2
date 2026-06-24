#include "Bureaucrat.hpp"

int main()
{
    {
        Bureaucrat a("Alice", 75);
        std::cout << a << std::endl;
    }

    {
        Bureaucrat b("Bob", 3);
        std::cout << b << std::endl;
        b.incrementGrade();
        std::cout << b << std::endl;
    }

    {
        Bureaucrat c("Carol", 148);
        std::cout << c << std::endl;
        c.decrementGrade();
        std::cout << c << std::endl;
    }

    try
    {
        Bureaucrat d("Dan", 0);
        std::cout << d << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try
    {
        Bureaucrat e("Eve", 151);
        std::cout << e << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try
    {
        Bureaucrat f("Frank", 1);
        std::cout << f << std::endl;
        f.incrementGrade();
    }
    catch (std::exception &e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try
    {
        Bureaucrat g("Grace", 150);
        std::cout << g << std::endl;
        g.decrementGrade();
    }
    catch (std::exception &e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}