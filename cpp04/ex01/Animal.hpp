#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal
{
	protected:
		std::string	type;

	public:
		Animal(void);
		Animal(std::string const &type);
		Animal(Animal const &src);
		Animal &operator=(Animal const &rhs);
		virtual ~Animal(void);

		virtual void		makeSound(void) const;
		std::string const	&getType(void) const;
};

#endif
