#include "WrongCat.hpp"

// -------------------------------- 正準形 ----------------------------------

WrongCat::WrongCat(void) : WrongAnimal("WrongCat")
{
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(WrongCat const &src) : WrongAnimal(src)
{
	std::cout << "WrongCat copy constructor called" << std::endl;
	*this = src;
}

// WrongCat は自前のメンバを持たないので、基底クラスに丸ごと任せる。
WrongCat &WrongCat::operator=(WrongCat const &rhs)
{
	std::cout << "WrongCat copy assignment operator called" << std::endl;
	if (this != &rhs)
		WrongAnimal::operator=(rhs);
	return (*this);
}

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat destructor called" << std::endl;
}

// --------------------------------- 鳴き声 ---------------------------------

// WrongCat 型の変数から直接呼んだときにだけ実行される。
// WrongAnimal* 越しでは基底の makeSound が選ばれてしまう。
void	WrongCat::makeSound(void) const
{
	std::cout << "Meow! Meow! (but you will never hear it)" << std::endl;
}
