#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain	*_brain;

	public:
		Cat(void);
		Cat(Cat const &src);
		Cat &operator=(Cat const &rhs);
		virtual ~Cat(void);

		virtual void	makeSound(void) const;

		Brain		*getBrain(void) const;
		void		setIdea(int index, std::string const &idea);
		std::string const	&getIdea(int index) const;
};

#endif
