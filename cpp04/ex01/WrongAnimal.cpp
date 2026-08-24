#include "WrongAnimal.hpp"

// -------------------------------- 正準形 ----------------------------------

WrongAnimal::WrongAnimal(void) : type("WrongAnimal")
{
	std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string const &type) : type(type)
{
	std::cout << "WrongAnimal constructor called for type " << this->type << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &src)
{
	std::cout << "WrongAnimal copy constructor called" << std::endl;
	*this = src;
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal const &rhs)
{
	std::cout << "WrongAnimal copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->type = rhs.type;
	return (*this);
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WrongAnimal destructor called" << std::endl;
}

// --------------------------------- 鳴き声 ---------------------------------

// virtual ではないので、WrongAnimal* から呼ぶと中身が WrongCat であっても
// 必ずこちらが実行される。
void	WrongAnimal::makeSound(void) const
{
	std::cout << "* a wrong animal makes a wrong noise *" << std::endl;
}

std::string const	&WrongAnimal::getType(void) const
{
	return (this->type);
}
