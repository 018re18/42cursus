#include "Brain.hpp"

Brain::Brain(void)
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "...";
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(Brain const &src)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = src;
}

Brain &Brain::operator=(Brain const &rhs)
{
	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		for (int i = 0; i < 100; i++)
			this->ideas[i] = rhs.ideas[i];
	}
	return (*this);
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor called" << std::endl;
}

void	Brain::setIdea(int index, std::string const &idea)
{
	if (index < 0 || index >= 100)
	{
		std::cout << "Brain: idea index " << index << " is out of range"
			<< std::endl;
		return ;
	}
	this->ideas[index] = idea;
}

std::string const	&Brain::getIdea(int index) const
{
	static const std::string	nothing = "(no such idea)";

	if (index < 0 || index >= 100)
		return (nothing);
	return (this->ideas[index]);
}
