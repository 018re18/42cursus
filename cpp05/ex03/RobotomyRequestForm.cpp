#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <ctime>

// -------------------------------- 正準形 ----------------------------------

RobotomyRequestForm::RobotomyRequestForm(void)
	: AForm("RobotomyRequestForm", 72, 45), _target("default")
{
	std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string const &target)
	: AForm("RobotomyRequestForm", 72, 45), _target(target)
{
	std::cout << "RobotomyRequestForm constructor called for " << this->_target << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &src)
	: AForm(src), _target(src._target)
{
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &rhs)
{
	std::cout << "RobotomyRequestForm copy assignment operator called" << std::endl;
	if (this != &rhs)
		AForm::operator=(rhs);
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

// -------------------------------- ゲッター --------------------------------

std::string const	&RobotomyRequestForm::getTarget(void) const
{
	return (this->_target);
}

// -------------------------------- 実処理 ----------------------------------

// 乱数の種は最初の実行時に一度だけ蒔く。
// 関数内 static なので初期化のタイミングが明確で、main を汚さずに済む。
static void	seedOnce(void)
{
	static bool	seeded = false;

	if (!seeded)
	{
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		seeded = true;
	}
}

void	RobotomyRequestForm::_executeAction(void) const
{
	seedOnce();
	std::cout << "* ドリルの音 : VRRRRRRRRRR... BZZZZZT *" << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << this->_target << " has been robotomized successfully" << std::endl;
	else
		std::cout << "the robotomy of " << this->_target << " failed" << std::endl;
}
