#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"

// WrongAnimal を継承した猫。makeSound を定義してはいるが、基底の makeSound が
// virtual ではないため、WrongAnimal* 経由では決して呼ばれない。
class WrongCat : public WrongAnimal
{
	public:
		// 直交正準形 (Orthodox Canonical Form)
		WrongCat(void);
		WrongCat(WrongCat const &src);
		WrongCat &operator=(WrongCat const &rhs);
		~WrongCat(void);

		void	makeSound(void) const;
};

#endif
