#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));   // so robotomy result varies between runs

    // 1. Shrubbery — high grade signs and executes (writes a file)
    {
        std::cout << "=== Shrubbery ===" << std::endl;
        Bureaucrat high("High", 1);
        ShrubberyCreationForm shrub("garden");
        high.signForm(shrub);
        high.executeForm(shrub);   // creates garden_shrubbery file
    }

    // 2. Robotomy — capable bureaucrat
    {
        std::cout << "\n=== Robotomy ===" << std::endl;
        Bureaucrat mid("Mid", 40);
        RobotomyRequestForm robo("Bender");
        mid.signForm(robo);
        mid.executeForm(robo);
    }

    // 3. Presidential pardon — needs very high grade
    {
        std::cout << "\n=== Pardon ===" << std::endl;
        Bureaucrat boss("Boss", 1);
        PresidentialPardonForm pardon("Arthur");
        boss.signForm(pardon);
        boss.executeForm(pardon);
    }

    // 4. Execute an UNSIGNED form — should fail
    {
        std::cout << "\n=== Unsigned execute ===" << std::endl;
        Bureaucrat boss("Boss", 1);
        PresidentialPardonForm pardon("Ford");
        boss.executeForm(pardon);   // never signed -> FormNotSigned
    }

    // 5. Sign OK but grade too low to execute
    {
        std::cout << "\n=== Grade too low to execute ===" << std::endl;
        Bureaucrat weak("Weak", 10);   // can sign (needs 25), cannot execute (needs 5)
        PresidentialPardonForm pardon("Trillian");
        weak.signForm(pardon);         // should succeed
        weak.executeForm(pardon);      // should fail: grade too low
    }

    // 6. Polymorphism: execute through an AForm pointer
    {
        std::cout << "\n=== Polymorphism via AForm* ===" << std::endl;
        Bureaucrat boss("Boss", 1);
        AForm *f = new RobotomyRequestForm("PolyTarget");
        boss.signForm(*f);
        boss.executeForm(*f);   // runs RobotomyRequestForm::execute
        delete f;               // virtual destructor ensures proper cleanup
    }

    return 0;
}