#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
    std::cout << "===== TEST 1: ShrubberyCreationForm — full success =====" << std::endl;
    try
    {
        Bureaucrat gardener("Gardener", 130);   // can sign (≤145) AND execute (≤137)
        ShrubberyCreationForm shrub("garden");

        std::cout << shrub << std::endl;
        gardener.signForm(shrub);
        gardener.executeForm(shrub);
        std::cout << "(check the file: garden_shrubbery)" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 2: RobotomyRequestForm — full success =====" << std::endl;
    try
    {
        Bureaucrat scientist("Dr. Strange", 40);   // can sign (≤72) AND execute (≤45)
        RobotomyRequestForm robo("Bender");

        scientist.signForm(robo);
        std::cout << "--- Running 4 attempts to see randomness ---" << std::endl;
        for (int i = 0; i < 4; ++i)
        {
            std::cout << "Attempt " << (i + 1) << ": ";
            scientist.executeForm(robo);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 3: PresidentialPardonForm — full success =====" << std::endl;
    try
    {
        Bureaucrat president("President", 1);   // can sign (≤25) AND execute (≤5)
        PresidentialPardonForm pardon("Arthur Dent");

        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 4: Grade too low to SIGN =====" << std::endl;
    try
    {
        Bureaucrat intern("Intern", 140);
        ShrubberyCreationForm shrub("forest");
        RobotomyRequestForm robo("HAL");
        PresidentialPardonForm pardon("Trillian");

        intern.signForm(shrub);     // grade 140 ≤ 145 → OK
        intern.signForm(robo);      // grade 140 > 72  → FAIL
        intern.signForm(pardon);    // grade 140 > 25  → FAIL
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 5: Can sign but cannot EXECUTE =====" << std::endl;
    try
    {
        Bureaucrat midRank("MidRank", 140);   // can sign shrub (≤145), can't execute (>137)
        ShrubberyCreationForm shrub("backyard");

        midRank.signForm(shrub);
        midRank.executeForm(shrub);   // grade 140 > 137 → FAIL
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 6: Execute an UNSIGNED form =====" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 1);
        ShrubberyCreationForm shrub("park");
        RobotomyRequestForm robo("R2D2");
        PresidentialPardonForm pardon("Ford Prefect");

        // Try executing without signing → FormNotSignedException
        boss.executeForm(shrub);
        boss.executeForm(robo);
        boss.executeForm(pardon);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 7: Polymorphism via AForm pointer =====" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 1);

        // Array of AForm* — polymorphism in action
        AForm* forms[3];
        forms[0] = new ShrubberyCreationForm("forest");
        forms[1] = new RobotomyRequestForm("C3PO");
        forms[2] = new PresidentialPardonForm("Marvin");

        for (int i = 0; i < 3; ++i)
        {
            std::cout << *forms[i] << std::endl;
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
            std::cout << std::endl;
        }

        // Cleanup — virtual destructor ensures derived destructors run!
        for (int i = 0; i < 3; ++i)
            delete forms[i];
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== TEST 8: Invalid construction grades =====" << std::endl;
    try
    {
        // Concrete forms don't take grade params, so we can't break them
        // through construction — they always use the canonical grades.
        // But we can still test the AForm constructor indirectly.
        // (Not much to test here for concrete forms — their grades are fixed.)
        std::cout << "Concrete forms use fixed canonical grades — no test needed here."
                  << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== END OF TESTS =====" << std::endl;
    return (0);
}