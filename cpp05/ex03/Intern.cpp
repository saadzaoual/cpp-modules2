#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// ===== Orthodox Canonical Form =====

Intern::Intern()
{
    std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(const Intern& /* copy */)
{
    std::cout << "Intern copy constructor called" << std::endl;
}

Intern& Intern::operator=(const Intern& /* other */)
{
    std::cout << "Intern copy assignment operator called" << std::endl;
    return (*this);
}

Intern::~Intern()
{
    std::cout << "Intern destructor called" << std::endl;
}

// ===== Static helper functions (private) =====

AForm* Intern::createShrubbery(const std::string& target)
{
    return (new ShrubberyCreationForm(target));
}

AForm* Intern::createRobotomy(const std::string& target)
{
    return (new RobotomyRequestForm(target));
}

AForm* Intern::createPardon(const std::string& target)
{
    return (new PresidentialPardonForm(target));
}

// ===== The factory method =====

AForm* Intern::makeForm(const std::string& formName, const std::string& target)
{
    const std::string names[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    AForm* (*creators[3])(const std::string&) = {
        &Intern::createShrubbery,
        &Intern::createRobotomy,
        &Intern::createPardon
    };

    for (int i = 0; i < 3; ++i)
    {
        if (names[i] == formName)
        {
            std::cout << "Intern creates " << formName << std::endl;
            return (creators[i](target));
        }
    }

    std::cerr << "Intern can't make " << formName
              << ": form does not exist" << std::endl;
    return (NULL);
}