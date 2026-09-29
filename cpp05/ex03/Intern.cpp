#include "Intern.hpp"

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

// -------------------------------- 生成関数 --------------------------------

AForm	*Intern::_createShrubberyCreationForm(std::string const &target)
{
	return (new ShrubberyCreationForm(target));
}

AForm	*Intern::_createRobotomyRequestForm(std::string const &target)
{
	return (new RobotomyRequestForm(target));
}

AForm	*Intern::_createPresidentialPardonForm(std::string const &target)
{
	return (new PresidentialPardonForm(target));
}

// -------------------------------- 対応表 ----------------------------------

// 書類が増えたらここに 1 行足すだけでよい。makeForm 本体は触らない。
Intern::FormEntry const	Intern::_forms[] =
{
	{ "shrubbery creation", &Intern::_createShrubberyCreationForm },
	{ "robotomy request", &Intern::_createRobotomyRequestForm },
	{ "presidential pardon", &Intern::_createPresidentialPardonForm }
};

int const	Intern::_formCount = sizeof(Intern::_forms) / sizeof(Intern::_forms[0]);

// -------------------------------- 正準形 ----------------------------------

Intern::Intern(void)
{
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(Intern const &src)
{
	std::cout << "Intern copy constructor called" << std::endl;
	*this = src;
}

// 状態を持たないので、代入しても何もコピーするものがない。
Intern &Intern::operator=(Intern const &rhs)
{
	std::cout << "Intern copy assignment operator called" << std::endl;
	(void)rhs;
	return (*this);
}

Intern::~Intern(void)
{
	std::cout << "Intern destructor called" << std::endl;
}

// -------------------------------- 書類作成 --------------------------------

AForm	*Intern::makeForm(std::string const &formName, std::string const &target) const
{
	for (int i = 0; i < _formCount; i++)
	{
		if (formName == _forms[i].name)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (_forms[i].create(target));
		}
	}
	std::cerr << "Intern: \"" << formName
		<< "\" such a form does not exist" << std::endl;
	return (NULL);
}
