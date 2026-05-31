#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
    : _name("default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
    std::cout << "Form default constructor called for " << _name << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name),
      _isSigned(false),
      _gradeToSign(gradeToSign),
      _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
    std::cout << "Form " << _name << " created (sign: " << _gradeToSign
              << ", exec: " << _gradeToExecute << ")" << std::endl;
}

Form::Form(const Form& copy)
    : _name(copy._name),
      _isSigned(copy._isSigned),
      _gradeToSign(copy._gradeToSign),
      _gradeToExecute(copy._gradeToExecute)
{
    std::cout << "Form copy constructor called for " << _name << std::endl;
}

Form& Form::operator=(const Form& other)
{
    std::cout << "Form copy assignment operator called" << std::endl;
    if (this != &other)
        _isSigned = other._isSigned;
    return (*this);
}

Form::~Form()
{
    std::cout << "Form destructor called for " << _name << std::endl;
}

std::string Form::getName() const
{
    return (_name);
}

bool Form::getIsSigned() const
{
    return (_isSigned);
}

int Form::getGradeToSign() const
{
    return (_gradeToSign);
}

int Form::getGradeToExecute() const
{
    return (_gradeToExecute);
}

void Form::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return ("Form grade is too high (must be >= 1)");
}

const char* Form::GradeTooLowException::what() const throw()
{
    return ("Form grade is too low (must be <= 150)");
}

std::ostream& operator<<(std::ostream& out, const Form& form)
{
    out << "Form \"" << form.getName() << "\" "
        << "[signed: " << (form.getIsSigned() ? "yes" : "no") << ", "
        << "grade to sign: " << form.getGradeToSign() << ", "
        << "grade to execute: " << form.getGradeToExecute() << "]";
    return (out);
}