#include "Dog.hpp"

// -------------------------------- 正準形 ----------------------------------

Dog::Dog(void) : Animal("Dog"), _brain(new Brain())
{
	std::cout << "Dog default constructor called" << std::endl;
}

// 元の Brain のポインタを写すのではなく、中身から新しい Brain を作る。
Dog::Dog(Dog const &src) : Animal(src), _brain(new Brain(*src._brain))
{
	std::cout << "Dog copy constructor called" << std::endl;
}

// こちらは既に自分の Brain を持っているので、作り直さず中身だけ写す。
Dog &Dog::operator=(Dog const &rhs)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		Animal::operator=(rhs);
		*this->_brain = *rhs._brain;
	}
	return (*this);
}

// 自分で new した Brain は自分で delete する。
Dog::~Dog(void)
{
	delete this->_brain;
	std::cout << "Dog destructor called" << std::endl;
}

// --------------------------------- 鳴き声 ---------------------------------

void	Dog::makeSound(void) const
{
	std::cout << "Woof! Woof!" << std::endl;
}

// ---------------------------- Brain への橋渡し -----------------------------

Brain	*Dog::getBrain(void) const
{
	return (this->_brain);
}

void	Dog::setIdea(int index, std::string const &idea)
{
	this->_brain->setIdea(index, idea);
}

std::string const	&Dog::getIdea(int index) const
{
	return (this->_brain->getIdea(index));
}
