#include "Animal.hpp"

// -------------------------------- 正準形 ----------------------------------

Animal::Animal(void) : type("Animal")
{
	std::cout << "Animal default constructor called" << std::endl;
}

// 派生クラスがここに自分の型名 ("Cat" など) を渡してくる。
Animal::Animal(std::string const &type) : type(type)
{
	std::cout << "Animal constructor called for type " << this->type << std::endl;
}

Animal::Animal(Animal const &src)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = src;
}

Animal &Animal::operator=(Animal const &rhs)
{
	std::cout << "Animal copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->type = rhs.type;
	return (*this);
}

Animal::~Animal(void)
{
	std::cout << "Animal destructor called" << std::endl;
}

// --------------------------------- 鳴き声 ---------------------------------

// 派生クラスが上書きする既定の鳴き声。
void	Animal::makeSound(void) const
{
	std::cout << "* an animal makes an indistinct noise *" << std::endl;
}

std::string const	&Animal::getType(void) const
{
	return (this->type);
}
