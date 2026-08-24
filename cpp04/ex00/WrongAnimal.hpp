#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <iostream>
#include <string>

// Animal と同じ形だが、makeSound を **わざと** virtual にしていないクラス。
// WrongAnimal* に WrongCat を入れて makeSound を呼ぶと、実際の型ではなく
// ポインタの型のほうが選ばれてしまう。virtual の効果を対比するための例。
class WrongAnimal
{
	protected:
		std::string	type;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		WrongAnimal(void);
		WrongAnimal(WrongAnimal const &src);
		WrongAnimal &operator=(WrongAnimal const &rhs);
		// デストラクタも virtual ではないので、WrongAnimal* 越しの delete では
		// WrongCat のデストラクタが呼ばれない
		~WrongAnimal(void);

		WrongAnimal(std::string const &type);

		void				makeSound(void) const;
		std::string const	&getType(void) const;
};

#endif
