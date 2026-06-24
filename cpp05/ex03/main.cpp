#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"

int main()
{
    Intern intern;
    Bureaucrat boss("Boss", 1);

    // 1. Valid form
    AForm *form = intern.makeForm("robotomy request", "Bender");
    if (form)
    {
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;            // caller owns the heap memory
    }

    // 2. Another valid form
    AForm *form2 = intern.makeForm("presidential pardon", "Arthur");
    if (form2)
    {
        boss.signForm(*form2);
        boss.executeForm(*form2);
        delete form2;
    }

    // 3. Unknown form name -> NULL, error message
    AForm *bad = intern.makeForm("coffee request", "Me");
    if (bad)
        delete bad;
    else
        std::cout << "(no form created)" << std::endl;

    return 0;
}