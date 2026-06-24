#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("default"), _is_signed(false), _sign_grade(50), _execute_grade(50)
{
}

AForm::AForm(const std::string &name, const int sign_grade, const int execute_grade) : _name(name), _is_signed(false), _sign_grade(sign_grade), _execute_grade(execute_grade)
{
    if (sign_grade < 1 || execute_grade < 1)
        throw GradeTooHighException();
    if (sign_grade > 150 || execute_grade > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm &copy)
    : _name(copy._name), _is_signed(copy._is_signed),
      _sign_grade(copy._sign_grade), _execute_grade(copy._execute_grade)
{
}

AForm &AForm::operator=(const AForm &other)
{
    if (this != &other)
        _is_signed = other._is_signed;
    return *this;
}

AForm::~AForm()
{
}

const std::string   &AForm::getName() const
{
    return _name;
}

bool    AForm::getIs_Signed() const
{
    return _is_signed;
}

int   AForm::getSign_Grade() const
{
    return _sign_grade;
}

int   AForm::getExecute_Grade() const
{
    return _execute_grade;
}

const char *AForm::GradeTooHighException::what() const throw()
{
    return "Grade is too high.";
}

const char *AForm::GradeTooLowException::what() const throw()
{
    return "Grade is too low.";
}

std::ostream &operator<<(std::ostream &os,  AForm const &form)
{
   os << "Name: " << form.getName() << " isSigned: " << form.getIs_Signed() << " SignGrade: " << form.getSign_Grade() << " ExecuteGrade: " << form.getExecute_Grade() << std::endl;
	return (os);
}

void    AForm::beSigned(const Bureaucrat &b)
{
    if(b.getGrade() <= _sign_grade)
        _is_signed = true;
    else
        throw GradeTooLowException();
}