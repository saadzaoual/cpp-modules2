#ifndef INTERN_HPP
#define INTERN_HPP

#include "Bureaucrat.hpp"

class AForm;
class Intern
{
    private:
        static AForm *makeShrubbery(const std::string &target);
        static AForm *makeRobotomy(const std::string &target);
        static AForm *makePardon(const std::string &target);
    public:
        Intern();
        Intern(const Intern &copy);
        Intern &operator=(const Intern &other);
        ~Intern();
    AForm *makeForm(const std::string &formName, const std::string &target);
};
#endif