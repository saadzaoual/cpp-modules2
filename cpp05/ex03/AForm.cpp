#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
    : _name("default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
    std::cout << "AForm default constructor called for " << _name << std::endl;
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name),
      _isSigned(false),
      _gradeToSign(gradeToSign),
      _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
    std::cout << "AForm " << _name << " created (sign: " << _gradeToSign
              << ", exec: " << _gradeToExecute << ")" << std::endl;
}

AForm::AForm(const AForm& copy)
    : _name(copy._name),
      _isSigned(copy._isSigned),
      _gradeToSign(copy._gradeToSign),
      _gradeToExecute(copy._gradeToExecute)
{
    std::cout << "AForm copy constructor called for " << _name << std::endl;
}

AForm& AForm::operator=(const AForm& other)
{
    std::cout << "AForm copy assignment operator called" << std::endl;
    if (this != &other)
        _isSigned = other._isSigned;
    return (*this);
}

AForm::~AForm()
{
    std::cout << "AForm destructor called for " << _name << std::endl;
}

std::string AForm::getName() const
{
    return (_name);
}

bool AForm::getIsSigned() const
{
    return (_isSigned);
}

int AForm::getGradeToSign() const
{
    return (_gradeToSign);
}

int AForm::getGradeToExecute() const
{
    return (_gradeToExecute);
}

void AForm::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return ("AForm grade is too high (must be >= 1)");
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return ("AForm grade is too low (must be <= 150)");
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return ("Form is not signed and cannot be executed");
}

void AForm::checkExecution(const Bureaucrat& executor) const
{
    if (!_isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& out, const AForm& form)
{
    out << "AForm \"" << form.getName() << "\" "
        << "[signed: " << (form.getIsSigned() ? "yes" : "no") << ", "
        << "grade to sign: " << form.getGradeToSign() << ", "
        << "grade to execute: " << form.getGradeToExecute() << "]";
    return (out);
}