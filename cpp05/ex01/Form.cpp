#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("default"), _is_signed(false), _sign_grade(50), _execute_grade(50)
{
}

Form::Form(const std::string &name, const int sign_grade, const int execute_grade) : _name(name), _is_signed(false), _sign_grade(sign_grade), _execute_grade(execute_grade)
{
    if (sign_grade < 1 || execute_grade < 1)
        throw GradeTooHighException();
    if (sign_grade > 150 || execute_grade > 150)
        throw GradeTooLowException();
}

Form::Form(const Form &copy)
    : _name(copy._name), _is_signed(copy._is_signed),
      _sign_grade(copy._sign_grade), _execute_grade(copy._execute_grade)
{
}

Form &Form::operator=(const Form &other)
{
    if (this != &other)
        _is_signed = other._is_signed;
    return *this;
}

Form::~Form()
{
}

const std::string   &Form::getName() const
{
    return _name;
}

bool    Form::getIs_Signed() const
{
    return _is_signed;
}

int   Form::getSign_Grade() const
{
    return _sign_grade;
}

int   Form::getExecute_Grade() const
{
    return _execute_grade;
}

const char *Form::GradeTooHighException::what() const throw()
{
    return "Grade is too high.";
}

const char *Form::GradeTooLowException::what() const throw()
{
    return "Grade is too low.";
}

std::ostream &operator<<(std::ostream &os,  Form const &form)
{
   os << "Name: " << form.getName() << " isSigned: " << form.getIs_Signed() << " SignGrade: " << form.getSign_Grade() << " ExecuteGrade: " << form.getExecute_Grade() << std::endl;
	return (os);
}

void    Form::beSigned(const Bureaucrat &b)
{
    if(b.getGrade() <= _sign_grade)
        _is_signed = true;
    else
        throw GradeTooLowException();
}