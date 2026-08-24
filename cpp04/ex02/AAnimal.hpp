#ifndef AANIMAL_HPP
# define AANIMAL_HPP

#include <iostream>
#include <string>

// 動物の抽象基底クラス。
// makeSound が純粋仮想関数 (= 0) なので、AAnimal そのものは実体を作れない。
// 「動物一般の鳴き声」という中身のないものを禁じつつ、AAnimal* 越しに
// 実際の型 (Cat / Dog) の鳴き声を鳴らせるようにしている。
class AAnimal
{
	protected:
		// 実際の型を表す文字列。派生クラスがコンストラクタで設定する
		std::string	type;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		AAnimal(void);
		AAnimal(AAnimal const &src);
		AAnimal &operator=(AAnimal const &rhs);
		// AAnimal* 越しに delete しても派生クラスのデストラクタが走るよう virtual
		virtual ~AAnimal(void);

		AAnimal(std::string const &type);

		// 純粋仮想関数。派生クラスは必ず自分の鳴き声を定義しなければならない
		virtual void		makeSound(void) const = 0;
		std::string const	&getType(void) const;
};

#endif
