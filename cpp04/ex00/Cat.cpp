#include "Cat.hpp"

// -------------------------------- 正準形 ----------------------------------

// 基底クラスに自分の型名を渡すことで、getType() が "Cat" を返すようになる。
Cat::Cat(void) : Animal("Cat")
{
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(Cat const &src) : Animal(src)
{
	std::cout << "Cat copy constructor called" << std::endl;
	*this = src;
}

// Cat は自前のメンバを持たないので、基底クラスに丸ごと任せる。
Cat &Cat::operator=(Cat const &rhs)
{
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this != &rhs)
		Animal::operator=(rhs);
	return (*this);
}

Cat::~Cat(void)
{
	std::cout << "Cat destructor called" << std::endl;
}

// --------------------------------- 鳴き声 ---------------------------------

void	Cat::makeSound(void) const
{
	std::cout << "Meow! Meow!" << std::endl;
}
