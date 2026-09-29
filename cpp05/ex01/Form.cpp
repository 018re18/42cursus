#include "Form.hpp"
#include "Bureaucrat.hpp"

// -------------------------------- 正準形 ----------------------------------

Form::Form(void)
	: _name("default"), _isSigned(false),
	  _gradeToSign(Bureaucrat::LowestGrade), _gradeToExecute(Bureaucrat::LowestGrade)
{
	std::cout << "Form default constructor called" << std::endl;
}

// 生成時は必ず未署名。等級が範囲外なら例外を投げて生成を中止する。
Form::Form(std::string const &name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false),
	  _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	_checkGrade(gradeToSign);
	_checkGrade(gradeToExecute);
	std::cout << "Form constructor called for " << this->_name << std::endl;
}

Form::Form(Form const &src)
	: _name(src._name), _isSigned(src._isSigned),
	  _gradeToSign(src._gradeToSign), _gradeToExecute(src._gradeToExecute)
{
	std::cout << "Form copy constructor called" << std::endl;
}

// 名前も必要等級も const なので、代入できるのは署名状態だけ。
Form &Form::operator=(Form const &rhs)
{
	std::cout << "Form copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_isSigned = rhs._isSigned;
	return (*this);
}

Form::~Form(void)
{
	std::cout << "Form destructor called for " << this->_name << std::endl;
}

// -------------------------------- 等級の検査 ------------------------------

// 必要等級も官僚と同じ 1 〜 150 の範囲に収まっていなければならない。
void	Form::_checkGrade(int grade)
{
	if (grade < Bureaucrat::HighestGrade)
		throw Form::GradeTooHighException();
	if (grade > Bureaucrat::LowestGrade)
		throw Form::GradeTooLowException();
}

// -------------------------------- ゲッター --------------------------------

std::string const	&Form::getName(void) const
{
	return (this->_name);
}

bool	Form::getIsSigned(void) const
{
	return (this->_isSigned);
}

int	Form::getGradeToSign(void) const
{
	return (this->_gradeToSign);
}

int	Form::getGradeToExecute(void) const
{
	return (this->_gradeToExecute);
}

// -------------------------------- 署名 ------------------------------------

// 等級は数字が小さいほど上位。署名に必要な等級「以上」= 値が「以下」。
void	Form::beSigned(Bureaucrat const &bureaucrat)
{
	if (bureaucrat.getGrade() > this->_gradeToSign)
		throw Form::GradeTooLowException();
	this->_isSigned = true;
}

// -------------------------------- 例外 ------------------------------------

char const	*Form::GradeTooHighException::what(void) const throw()
{
	return ("Form::GradeTooHighException: grade is too high");
}

char const	*Form::GradeTooLowException::what(void) const throw()
{
	return ("Form::GradeTooLowException: grade is too low");
}

// -------------------------------- 出力 ------------------------------------

std::ostream	&operator<<(std::ostream &os, Form const &rhs)
{
	os << "Form " << rhs.getName()
		<< " [signed: " << (rhs.getIsSigned() ? "yes" : "no")
		<< ", grade to sign: " << rhs.getGradeToSign()
		<< ", grade to execute: " << rhs.getGradeToExecute() << "]";
	return (os);
}
