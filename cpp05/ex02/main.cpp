#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    {
        std::cout << "=== Shrubbery ===" << std::endl;
        Bureaucrat high("High", 1);
        ShrubberyCreationForm shrub("garden");
        high.signForm(shrub);
        high.executeForm(shrub); 
    }

    {
        std::cout << "\n=== Robotomy ===" << std::endl;
        Bureaucrat mid("Mid", 40);
        RobotomyRequestForm robo("Bender");
        mid.signForm(robo);
        mid.executeForm(robo);
    }

    {
        std::cout << "\n=== Pardon ===" << std::endl;
        Bureaucrat boss("Boss", 1);
        PresidentialPardonForm pardon("Arthur");
        boss.signForm(pardon);
        boss.executeForm(pardon);
    }

    {
        std::cout << "\n=== Unsigned execute ===" << std::endl;
        Bureaucrat boss("Boss", 1);
        PresidentialPardonForm pardon("Ford");
        boss.executeForm(pardon);   
    }

    {
        std::cout << "\n=== Grade too low to execute ===" << std::endl;
        Bureaucrat weak("Weak", 10);  
        PresidentialPardonForm pardon("Trillian");
        weak.signForm(pardon);         
        weak.executeForm(pardon);    
    }

    {
        std::cout << "\n=== Polymorphism via AForm* ===" << std::endl;
        Bureaucrat boss("Boss", 1);
        AForm *f = new RobotomyRequestForm("PolyTarget");
        boss.signForm(*f);
        boss.executeForm(*f); 
        delete f;              
    }

    return 0;
}