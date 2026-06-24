#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm
{
    private:
        const std::string _name;
        bool              _is_signed;
        const int         _sign_grade;
        const int         _execute_grade;
    protected:
        void checkExcute(const Bureaucrat &executor) const;
    public:
        AForm();
        AForm(const std::string &name,const int sign_grade, const int excute_grade);
        AForm(const AForm &copy);
        AForm &operator=(const AForm &other);
        virtual ~AForm();

        const std::string   &getName() const;
        bool                 getIs_Signed() const;
        int            getSign_Grade() const;
        int             getExecute_Grade() const;

        void    beSigned(const Bureaucrat &b);
        virtual void    execute(const Bureaucrat &executor) const = 0;
        
        class GradeTooHighException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class FormNotSignedException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
};

std::ostream &operator<<(std::ostream &os,  AForm const &Aform);
#endif