#ifndef AANIMAL_HPP
# define AANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal
{
	protected:
		std::string	type;

	public:
		AAnimal(void);
		AAnimal(std::string const &type);
		AAnimal(AAnimal const &src);
		AAnimal &operator=(AAnimal const &rhs);
		virtual ~AAnimal(void);

		virtual void		makeSound(void) const = 0;
		std::string const	&getType(void) const;
};

#endif
