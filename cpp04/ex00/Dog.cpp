#include "Dog.hpp"

// -------------------------------- 正準形 ----------------------------------

// 基底クラスに自分の型名を渡すことで、getType() が "Dog" を返すようになる。
Dog::Dog(void) : Animal("Dog")
{
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(Dog const &src) : Animal(src)
{
	std::cout << "Dog copy constructor called" << std::endl;
	*this = src;
}

// Dog は自前のメンバを持たないので、基底クラスに丸ごと任せる。
Dog &Dog::operator=(Dog const &rhs)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &rhs)
		Animal::operator=(rhs);
	return (*this);
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called" << std::endl;
}

// --------------------------------- 鳴き声 ---------------------------------

void	Dog::makeSound(void) const
{
	std::cout << "Woof! Woof!" << std::endl;
}
