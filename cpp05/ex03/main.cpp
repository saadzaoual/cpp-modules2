#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main(void)
{
    std::cout << "===== TEST 1: Intern creates ShrubberyCreationForm =====" << std::endl;
    {
        Intern intern;
        Bureaucrat gardener("Gardener", 130);

        AForm* form = intern.makeForm("shrubbery creation", "garden");
        if (form != NULL)
        {
            std::cout << *form << std::endl;
            gardener.signForm(*form);
            gardener.executeForm(*form);
            delete form;
        }
    }

    std::cout << std::endl << "===== TEST 2: Intern creates RobotomyRequestForm =====" << std::endl;
    {
        Intern intern;
        Bureaucrat scientist("Dr. Strange", 40);

        AForm* form = intern.makeForm("robotomy request", "Bender");
        if (form != NULL)
        {
            std::cout << *form << std::endl;
            scientist.signForm(*form);
            scientist.executeForm(*form);
            delete form;
        }
    }

    std::cout << std::endl << "===== TEST 3: Intern creates PresidentialPardonForm =====" << std::endl;
    {
        Intern intern;
        Bureaucrat president("President", 1);

        AForm* form = intern.makeForm("presidential pardon", "Arthur Dent");
        if (form != NULL)
        {
            std::cout << *form << std::endl;
            president.signForm(*form);
            president.executeForm(*form);
            delete form;
        }
    }

    std::cout << std::endl << "===== TEST 4: Unknown form name (should return NULL) =====" << std::endl;
    {
        Intern intern;
        AForm* form = intern.makeForm("coffee machine repair", "espresso");
        if (form == NULL)
            std::cout << "Got NULL as expected — graceful failure." << std::endl;
        else
        {
            std::cout << "Unexpected: got a form. Cleaning up." << std::endl;
            delete form;
        }
    }

    std::cout << std::endl << "===== TEST 5: Case sensitivity check =====" << std::endl;
    {
        Intern intern;
        AForm* form = intern.makeForm("Shrubbery Creation", "garden");
        if (form == NULL)
            std::cout << "Got NULL — case sensitivity confirmed." << std::endl;
        else
        {
            std::cout << "Unexpected: got a form." << std::endl;
            delete form;
        }
    }

    std::cout << std::endl << "===== TEST 6: Full chain through a loop =====" << std::endl;
    {
        Intern intern;
        Bureaucrat boss("Boss", 1);

        const std::string formNames[3] = {
            "shrubbery creation",
            "robotomy request",
            "presidential pardon"
        };
        const std::string targets[3] = {
            "Anthropic",
            "HAL9000",
            "Marvin"
        };

        for (int i = 0; i < 3; ++i)
        {
            std::cout << "--- " << formNames[i] << " ---" << std::endl;
            AForm* form = intern.makeForm(formNames[i], targets[i]);
            if (form != NULL)
            {
                boss.signForm(*form);
                boss.executeForm(*form);
                delete form;
            }
            std::cout << std::endl;
        }
    }

    std::cout << std::endl << "===== TEST 7: Bureaucrat too weak to sign/execute =====" << std::endl;
    {
        Intern intern;
        Bureaucrat lowRank("LowRank", 100);

        AForm* form = intern.makeForm("presidential pardon", "TooLow");
        if (form != NULL)
        {
            lowRank.signForm(*form);     // grade 100 > 25 → fail to sign
            lowRank.executeForm(*form);  // not signed → FormNotSignedException
            delete form;
        }
    }

    std::cout << std::endl << "===== END OF TESTS =====" << std::endl;
    return (0);
}