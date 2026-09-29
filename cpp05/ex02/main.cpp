#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

// 署名 -> 実行 の一連の流れを、基底クラスのポインタ越しに試す。
static void	signAndExecute(Bureaucrat const &signer, Bureaucrat const &executor, AForm *form)
{
	std::cout << *form << std::endl;
	signer.signForm(*form);
	executor.executeForm(*form);
	std::cout << std::endl;
}

static void	nominalTest(void)
{
	std::cout << "=== 権限が十分な官僚による署名と実行 ===" << std::endl;

	Bureaucrat	boss("Boss", 1);
	AForm		*forms[3];

	forms[0] = new ShrubberyCreationForm("home");
	forms[1] = new RobotomyRequestForm("Bender");
	forms[2] = new PresidentialPardonForm("Arthur Dent");

	std::cout << std::endl;
	for (int i = 0; i < 3; i++)
		signAndExecute(boss, boss, forms[i]);

	for (int i = 0; i < 3; i++)
		delete forms[i];
	std::cout << std::endl;
}

static void	notSignedTest(void)
{
	std::cout << "=== 未署名の書類を実行しようとする ===" << std::endl;

	Bureaucrat				boss("Boss", 1);
	PresidentialPardonForm	form("Ford Prefect");

	std::cout << form << std::endl;
	// 署名していないので FormNotSignedException になる
	boss.executeForm(form);
	std::cout << std::endl;
}

static void	gradeTooLowTest(void)
{
	std::cout << "=== 署名はできるが実行の等級が足りない ===" << std::endl;

	// 署名 145 / 実行 137 なので、等級 140 は署名だけできる
	Bureaucrat				middle("Middle", 140);
	ShrubberyCreationForm	form("garden");

	std::cout << form << std::endl;
	middle.signForm(form);
	middle.executeForm(form);
	std::cout << std::endl;

	std::cout << "--- 等級 137 なら実行まで通る ---" << std::endl;
	Bureaucrat	higher("Higher", 137);
	higher.executeForm(form);
	std::cout << std::endl;
}

static void	robotomyRandomnessTest(void)
{
	std::cout << "=== ロボトミーを 6 回実行 (50% で成功) ===" << std::endl;

	Bureaucrat			boss("Boss", 1);
	RobotomyRequestForm	form("Marvin");

	boss.signForm(form);
	for (int i = 0; i < 6; i++)
		form.execute(boss);
	std::cout << std::endl;
}

// 木を書き込めない場所を target にして、失敗が失敗として報告されるか確かめる。
static void	fileFailureTest(void)
{
	std::cout << "=== ファイルを作れない場合 ===" << std::endl;

	Bureaucrat				boss("Boss", 1);
	ShrubberyCreationForm	form("/no_such_directory/tree");

	boss.signForm(form);
	// 黙って成功扱いにせず、couldn't execute と報告される
	boss.executeForm(form);

	// execute() を直接呼べば専用の例外を捕まえられる
	try
	{
		form.execute(boss);
		std::cout << "ここには到達しない" << std::endl;
	}
	catch (ShrubberyCreationForm::FileCreationFailedException &e)
	{
		std::cout << "例外: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

static void	polymorphismTest(void)
{
	std::cout << "=== AForm* 越しの delete で派生のデストラクタが走る ===" << std::endl;

	AForm	*form = new RobotomyRequestForm("Zaphod");

	delete form;
	std::cout << std::endl;
}

int	main(void)
{
	nominalTest();
	notSignedTest();
	gradeTooLowTest();
	robotomyRandomnessTest();
	fileFailureTest();
	polymorphismTest();
	return (0);
}
