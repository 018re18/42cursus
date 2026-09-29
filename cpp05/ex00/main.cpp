#include "Bureaucrat.hpp"

// 生成を試み、例外が飛んだらその内容を表示する。
static void	tryToCreate(std::string const &name, int grade)
{
	std::cout << "--- " << name << " (grade " << grade << ") を生成 ---" << std::endl;
	try
	{
		Bureaucrat	b(name, grade);
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "例外: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

static void	constructionTest(void)
{
	std::cout << "=== 生成時の等級チェック ===" << std::endl;
	tryToCreate("Alice", 1);
	tryToCreate("Bob", 150);
	tryToCreate("TooHigh", 0);
	tryToCreate("TooLow", 151);
}

static void	incrementTest(void)
{
	std::cout << "=== 昇格 (1 に近づく) ===" << std::endl;

	Bureaucrat	b("Climber", 3);

	try
	{
		std::cout << b << std::endl;
		b.incrementGrade();
		std::cout << "昇格 -> " << b << std::endl;
		b.incrementGrade();
		std::cout << "昇格 -> " << b << std::endl;
		// ここで grade 1 からさらに昇格しようとして例外が飛ぶ
		b.incrementGrade();
		std::cout << "ここには到達しない" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "例外: " << e.what() << std::endl;
	}
	// 例外が飛んでも等級は壊れていない
	std::cout << "例外後の状態: " << b << std::endl << std::endl;
}

static void	decrementTest(void)
{
	std::cout << "=== 降格 (150 に近づく) ===" << std::endl;

	Bureaucrat	b("Faller", 149);

	try
	{
		std::cout << b << std::endl;
		b.decrementGrade();
		std::cout << "降格 -> " << b << std::endl;
		b.decrementGrade();
		std::cout << "ここには到達しない" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "例外: " << e.what() << std::endl;
	}
	std::cout << "例外後の状態: " << b << std::endl << std::endl;
}

static void	canonicalFormTest(void)
{
	std::cout << "=== 正準形 (コピー・代入) ===" << std::endl;

	Bureaucrat	original("Original", 42);
	Bureaucrat	copy(original);

	std::cout << "コピー元: " << original << std::endl;
	std::cout << "コピー先: " << copy << std::endl;

	Bureaucrat	other("Other", 100);
	other = original;
	// 名前は const なので代入されず、等級だけが移る
	std::cout << "代入後  : " << other << std::endl << std::endl;
}

int	main(void)
{
	constructionTest();
	incrementTest();
	decrementTest();
	canonicalFormTest();
	return (0);
}
