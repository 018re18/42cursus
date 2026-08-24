#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>

// 動物の基底クラス。
// makeSound が virtual なので、Animal* 越しに呼んでも実際の型 (Cat / Dog) の
// 鳴き声が鳴る。virtual を外すと何が起きるかは WrongAnimal で確認できる。
class Animal
{
	protected:
		// 実際の型を表す文字列。派生クラスがコンストラクタで設定する
		std::string	type;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Animal(void);
		Animal(Animal const &src);
		Animal &operator=(Animal const &rhs);
		// Animal* 越しに delete しても派生クラスのデストラクタが走るよう virtual
		virtual ~Animal(void);

		Animal(std::string const &type);

		virtual void		makeSound(void) const;
		std::string const	&getType(void) const;
};

#endif
