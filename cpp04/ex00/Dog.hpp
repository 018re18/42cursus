#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"

// Animal を継承した犬。makeSound が virtual なので、Animal* に入れても
// 犬の鳴き声が鳴る。
class Dog : public Animal
{
	public:
		// 直交正準形 (Orthodox Canonical Form)
		Dog(void);
		Dog(Dog const &src);
		Dog &operator=(Dog const &rhs);
		virtual ~Dog(void);

		virtual void	makeSound(void) const;
};

#endif
