#include "AAnimal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

static void	abstractTest(void)
{
	std::cout << "=== AAnimal は抽象クラス ===" << std::endl;
	std::cout << "下の行はコンパイルできない。"
		<< "AAnimal は makeSound が純粋仮想関数だから:" << std::endl;
	std::cout << "    const AAnimal *meta = new AAnimal();" << std::endl;
	// const AAnimal	*meta = new AAnimal();
	// AAnimal		onTheStack;
	std::cout << std::endl;
}

static void	subjectTest(void)
{
	std::cout << "=== 課題のテスト ===" << std::endl;

	const AAnimal	*j = new Dog();
	const AAnimal	*i = new Cat();

	std::cout << std::endl << "--- 鳴き声 ---" << std::endl;
	j->makeSound();
	i->makeSound();

	std::cout << std::endl << "--- 破棄 (リークなし) ---" << std::endl;
	delete j;
	delete i;
	std::cout << std::endl;
}

static void	arrayTest(void)
{
	std::cout << "=== 半分が犬、半分が猫 ===" << std::endl;

	const int	size = 8;
	AAnimal		*animals[size];

	for (int k = 0; k < size; k++)
	{
		if (k < size / 2)
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

	std::cout << std::endl << "--- AAnimal* のまま全部 delete ---" << std::endl;
	for (int k = 0; k < size; k++)
		delete animals[k];
	std::cout << std::endl;
}

static void	deepCopyConstructorTest(void)
{
	std::cout << "=== ディープコピー: コピーコンストラクタ ===" << std::endl;

	Dog	original;

	original.setIdea(0, "骨が欲しい");
	original.setIdea(1, "散歩に行きたい");

	std::cout << std::endl << "--- コピー ---" << std::endl;
	Dog	copy(original);

	std::cout << std::endl << "--- コピーにも考えが引き継がれる ---" << std::endl;
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "copy[0]    : " << copy.getIdea(0) << std::endl;

	std::cout << std::endl << "--- Brain のアドレスが別であること ---" << std::endl;
	std::cout << "original brain: " << original.getBrain() << std::endl;
	std::cout << "copy brain    : " << copy.getBrain() << std::endl;
	std::cout << "ディープコピー: "
		<< (original.getBrain() != copy.getBrain() ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- コピーを変えても元は変わらない ---"
		<< std::endl;
	copy.setIdea(0, "骨が 2 本欲しい");
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "copy[0]    : " << copy.getIdea(0) << std::endl;
	std::cout << "独立している: "
		<< (original.getIdea(0) != copy.getIdea(0) ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- 破棄 ---" << std::endl;
}

static void	deepCopyAssignmentTest(void)
{
	std::cout << "=== ディープコピー: 代入演算子 ===" << std::endl;

	Cat	original;
	Cat	assigned;

	original.setIdea(0, "昼寝したい");
	assigned.setIdea(0, "特に何も");

	std::cout << std::endl << "--- 代入 ---" << std::endl;
	assigned = original;

	std::cout << std::endl << "--- 結果 ---" << std::endl;
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "assigned[0]: " << assigned.getIdea(0) << std::endl;
	std::cout << "original brain: " << original.getBrain() << std::endl;
	std::cout << "assigned brain: " << assigned.getBrain() << std::endl;
	std::cout << "ディープコピー: "
		<< (original.getBrain() != assigned.getBrain() ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- 元を変えてもコピーは変わらない ---"
		<< std::endl;
	original.setIdea(0, "昼寝を 2 回したい");
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "assigned[0]: " << assigned.getIdea(0) << std::endl;
	std::cout << "独立している: "
		<< (original.getIdea(0) != assigned.getIdea(0) ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- 自己代入しても壊れない ---" << std::endl;
	Cat	&alias = assigned;

	assigned = alias;
	std::cout << "assigned[0]: " << assigned.getIdea(0) << std::endl;

	std::cout << std::endl << "--- 破棄 ---" << std::endl;
}

static void	brainBoundsTest(void)
{
	std::cout << "=== Brain の範囲外アクセス ===" << std::endl;

	Brain	brain;

	std::cout << std::endl;
	brain.setIdea(99, "最後の考え");
	std::cout << "idea 99 : " << brain.getIdea(99) << std::endl;
	brain.setIdea(100, "範囲外 (大きすぎる番号)");
	std::cout << "idea 100: " << brain.getIdea(100) << std::endl;
	brain.setIdea(-1, "範囲外 (負の番号)");
	std::cout << "idea -1 : " << brain.getIdea(-1) << std::endl;

	std::cout << std::endl << "--- 破棄 ---" << std::endl;
}

int	main(void)
{
	abstractTest();
	subjectTest();
	arrayTest();
	deepCopyConstructorTest();
	std::cout << std::endl;
	deepCopyAssignmentTest();
	std::cout << std::endl;
	brainBoundsTest();
	std::cout << std::endl;
	return (0);
}
