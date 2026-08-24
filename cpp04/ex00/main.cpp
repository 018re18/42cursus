#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

static void	subjectTest(void)
{
	std::cout << "=== 課題のテスト ===" << std::endl;

	const Animal	*meta = new Animal();
	const Animal	*j = new Dog();
	const Animal	*i = new Cat();

	std::cout << std::endl << "--- 型 ---" << std::endl;
	std::cout << meta->getType() << " " << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	std::cout << std::endl << "--- Animal* 越しの鳴き声 ---" << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	std::cout << std::endl << "--- Animal* 越しの破棄 ---" << std::endl;
	delete meta;
	delete j;
	delete i;
	std::cout << std::endl;
}

static void	wrongTest(void)
{
	std::cout << "=== WrongAnimal のテスト ===" << std::endl;

	const WrongAnimal	*meta = new WrongAnimal();
	const WrongAnimal	*i = new WrongCat();

	std::cout << std::endl << "--- 型 ---" << std::endl;
	std::cout << meta->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	std::cout << std::endl << "--- WrongAnimal* 越しの鳴き声 ---" << std::endl;
	i->makeSound();
	meta->makeSound();
	std::cout << "(makeSound が virtual でないので、WrongCat の鳴き声は決して聞こえない)"
		<< std::endl;

	std::cout << std::endl << "--- 実際の型から呼んだ場合 ---" << std::endl;
	const WrongCat	realCat;

	realCat.makeSound();

	std::cout << std::endl << "--- 破棄 ---" << std::endl;
	delete meta;
	delete static_cast<const WrongCat *>(i);
	std::cout << std::endl;
}

static void	arrayTest(void)
{
	std::cout << "=== 多態な配列 ===" << std::endl;

	const int	size = 6;
	Animal		*animals[size];

	for (int k = 0; k < size; k++)
	{
		if (k % 2 == 0)
			animals[k] = new Dog();
		else
			animals[k] = new Cat();
	}

	std::cout << std::endl << "--- それぞれが鳴く ---" << std::endl;
	for (int k = 0; k < size; k++)
	{
		std::cout << "[" << k << "] " << animals[k]->getType() << ": ";
		animals[k]->makeSound();
	}

	std::cout << std::endl << "--- Animal* のまま全部 delete ---" << std::endl;
	for (int k = 0; k < size; k++)
		delete animals[k];
	std::cout << std::endl;
}

static void	copyTest(void)
{
	std::cout << "=== コピーの挙動 ===" << std::endl;

	Dog	original;

	std::cout << std::endl << "--- コピーコンストラクタ ---" << std::endl;
	Dog	copy(original);

	std::cout << std::endl << "--- コピー代入 ---" << std::endl;
	Dog	assigned;

	assigned = original;

	std::cout << std::endl << "--- コピーも犬として振る舞う ---" << std::endl;
	std::cout << copy.getType() << ": ";
	copy.makeSound();
	std::cout << assigned.getType() << ": ";
	assigned.makeSound();

	std::cout << std::endl << "--- 破棄 ---" << std::endl;
}

static void	sliceTest(void)
{
	std::cout << "=== 基底クラスの参照 (スライシングは起きない) ===" << std::endl;

	Cat				cat;
	Animal			&ref = cat;
	Animal const	&constRef = cat;

	std::cout << std::endl;
	std::cout << "ref (" << ref.getType() << "): ";
	ref.makeSound();
	std::cout << "constRef (" << constRef.getType() << "): ";
	constRef.makeSound();

	std::cout << std::endl << "--- 破棄 ---" << std::endl;
}

int	main(void)
{
	subjectTest();
	wrongTest();
	arrayTest();
	copyTest();
	std::cout << std::endl;
	sliceTest();
	std::cout << std::endl;
	return (0);
}
