#include "Cat.hpp"

// -------------------------------- 正準形 ----------------------------------

Cat::Cat(void) : Animal("Cat"), _brain(new Brain())
{
	std::cout << "Cat default constructor called" << std::endl;
}

// 元の Brain のポインタを写すのではなく、中身から新しい Brain を作る。
Cat::Cat(Cat const &src) : Animal(src), _brain(new Brain(*src._brain))
{
	std::cout << "Cat copy constructor called" << std::endl;
}

// こちらは既に自分の Brain を持っているので、作り直さず中身だけ写す。
Cat &Cat::operator=(Cat const &rhs)
{
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		Animal::operator=(rhs);
		*this->_brain = *rhs._brain;
	}
	return (*this);
}

// 自分で new した Brain は自分で delete する。
Cat::~Cat(void)
{
	delete this->_brain;
	std::cout << "Cat destructor called" << std::endl;
}

// --------------------------------- 鳴き声 ---------------------------------

void	Cat::makeSound(void) const
{
	std::cout << "Meow! Meow!" << std::endl;
}

// ---------------------------- Brain への橋渡し -----------------------------

Brain	*Cat::getBrain(void) const
{
	return (this->_brain);
}

void	Cat::setIdea(int index, std::string const &idea)
{
	this->_brain->setIdea(index, idea);
}

std::string const	&Cat::getIdea(int index) const
{
	return (this->_brain->getIdea(index));
}
