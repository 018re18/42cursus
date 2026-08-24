#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"

// Animal を継承した猫。makeSound が virtual なので、Animal* に入れても
// 猫の鳴き声が鳴る。
class Cat : public Animal
{
	public:
		// 直交正準形 (Orthodox Canonical Form)
		Cat(void);
		Cat(Cat const &src);
		Cat &operator=(Cat const &rhs);
		virtual ~Cat(void);

		virtual void	makeSound(void) const;
};

#endif
