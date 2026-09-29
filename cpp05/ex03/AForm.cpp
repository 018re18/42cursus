#include "AForm.hpp"
#include "Bureaucrat.hpp"

// -------------------------------- 正準形 ----------------------------------

AForm::AForm(void)
	: _name("default"), _isSigned(false),
	  _gradeToSign(Bureaucrat::LowestGrade), _gradeToExecute(Bureaucrat::LowestGrade)
{
	std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(std::string const &name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false),
	  _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	_checkGrade(gradeToSign);
	_checkGrade(gradeToExecute);
	std::cout << "AForm constructor called for " << this->_name << std::endl;
}

AForm::AForm(AForm const &src)
	: _name(src._name), _isSigned(src._isSigned),
	  _gradeToSign(src._gradeToSign), _gradeToExecute(src._gradeToExecute)
{
	std::cout << "AForm copy constructor called" << std::endl;
}

// const メンバは代入できないので、署名状態だけをコピーする。
AForm &AForm::operator=(AForm const &rhs)
{
	std::cout << "AForm copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_isSigned = rhs._isSigned;
	return (*this);
}

AForm::~AForm(void)
{
	std::cout << "AForm destructor called for " << this->_name << std::endl;
}

// -------------------------------- 等級の検査 ------------------------------

void	AForm::_checkGrade(int grade)
{
	if (grade < Bureaucrat::HighestGrade)
		throw AForm::GradeTooHighException();
	if (grade > Bureaucrat::LowestGrade)
		throw AForm::GradeTooLowException();
}

// -------------------------------- ゲッター --------------------------------

std::string const	&AForm::getName(void) const
{
	return (this->_name);
}

bool	AForm::getIsSigned(void) const
{
	return (this->_isSigned);
}

int	AForm::getGradeToSign(void) const
{
	return (this->_gradeToSign);
}

int	AForm::getGradeToExecute(void) const
{
	return (this->_gradeToExecute);
}

// -------------------------------- 署名 ------------------------------------

void	AForm::beSigned(Bureaucrat const &bureaucrat)
{
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}

// -------------------------------- 実行 ------------------------------------

// 共通の前提条件をここで一度だけ確認し、通れば派生クラスの処理を呼ぶ。
void	AForm::execute(Bureaucrat const &executor) const
{
	if (!this->_isSigned)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->_gradeToExecute)
		throw AForm::GradeTooLowException();
	this->_executeAction();
}

// -------------------------------- 例外 ------------------------------------

char const	*AForm::GradeTooHighException::what(void) const throw()
{
	return ("AForm::GradeTooHighException: grade is too high");
}

char const	*AForm::GradeTooLowException::what(void) const throw()
{
	return ("AForm::GradeTooLowException: grade is too low");
}

char const	*AForm::FormNotSignedException::what(void) const throw()
{
	return ("AForm::FormNotSignedException: the form is not signed");
}

// -------------------------------- 出力 ------------------------------------

std::ostream	&operator<<(std::ostream &os, AForm const &rhs)
{
	os << "AForm " << rhs.getName()
		<< " [signed: " << (rhs.getIsSigned() ? "yes" : "no")
		<< ", grade to sign: " << rhs.getGradeToSign()
		<< ", grade to execute: " << rhs.getGradeToExecute() << "]";
	return (os);
}
