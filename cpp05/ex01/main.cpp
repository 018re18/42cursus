#include "Bureaucrat.hpp"
#include "Form.hpp"

// 書類の生成を試み、等級が範囲外なら例外を表示する。
static void	tryToCreateForm(std::string const &name, int toSign, int toExec)
{
	std::cout << "--- " << name << " (sign " << toSign
		<< " / exec " << toExec << ") を生成 ---" << std::endl;
	try
	{
		Form	f(name, toSign, toExec);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "例外: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

static void	formConstructionTest(void)
{
	std::cout << "=== 書類の生成と等級チェック ===" << std::endl;
	tryToCreateForm("TaxForm", 50, 25);
	tryToCreateForm("Impossible", 0, 100);
	tryToCreateForm("AlsoImpossible", 100, 151);
}

static void	signTest(void)
{
	std::cout << "=== 署名 (signForm 経由) ===" << std::endl;

	Bureaucrat	boss("Boss", 1);
	Bureaucrat	intern("Intern", 150);
	Form		contract("Contract", 50, 25);

	std::cout << contract << std::endl;

	// 等級 150 では 50 に届かないので失敗する
	intern.signForm(contract);
	std::cout << contract << std::endl;

	// 等級 1 なら署名できる
	boss.signForm(contract);
	std::cout << contract << std::endl;

	// 署名済みの書類にもう一度署名しても、状態は署名済みのまま
	boss.signForm(contract);
	std::cout << std::endl;
}

static void	beSignedDirectTest(void)
{
	std::cout << "=== beSigned を直接呼ぶ (例外は呼び出し側で捕まえる) ===" << std::endl;

	Bureaucrat	weak("Weak", 100);
	Form		strict("Strict", 10, 5);

	try
	{
		strict.beSigned(weak);
		std::cout << "ここには到達しない" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "例外: " << e.what() << std::endl;
	}
	std::cout << strict << std::endl;

	// ちょうど必要等級と同じなら署名できる
	Bureaucrat	exact("Exact", 10);
	try
	{
		strict.beSigned(exact);
		std::cout << "等級ちょうどでも署名できる: " << strict << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "例外: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

int	main(void)
{
	formConstructionTest();
	signTest();
	beSignedDirectTest();
	return (0);
}
