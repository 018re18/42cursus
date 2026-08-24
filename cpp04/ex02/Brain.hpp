#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>
#include <string>

class Brain
{
	private:
		std::string	ideas[100];

	public:
		Brain(void);
		Brain(Brain const &src);
		Brain &operator=(Brain const &rhs);
		~Brain(void);

		void				setIdea(int index, std::string const &idea);
		std::string const	&getIdea(int index) const;
};

#endif
