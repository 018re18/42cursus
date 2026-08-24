#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

// Brain を 1 つ所有する犬。
// メンバがポインタなので、コピーではポインタではなく指し先の Brain を
// 複製する (ディープコピー)。そうしないと二重解放になる。
class Dog : public Animal
{
	private:
		Brain	*_brain;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Dog(void);
		Dog(Dog const &src);
		Dog &operator=(Dog const &rhs);
		virtual ~Dog(void);

		virtual void		makeSound(void) const;

		// ディープコピーを確かめるために Brain を外から覗くための窓口
		Brain				*getBrain(void) const;
		void				setIdea(int index, std::string const &idea);
		std::string const	&getIdea(int index) const;
};

#endif
