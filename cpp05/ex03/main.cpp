#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

// インターンに書類を作らせ、官僚に署名・実行させてから後片付けする。
static void	runForm(Intern const &intern, Bureaucrat const &bureaucrat,
					std::string const &formName, std::string const &target)
{
	std::cout << "--- \"" << formName << "\" / target: " << target << " ---" << std::endl;

	AForm	*form = intern.makeForm(formName, target);

	if (form == NULL)
	{
		std::cout << "書類が作れなかったので何もしない" << std::endl << std::endl;
		return ;
	}
	bureaucrat.signForm(*form);
	bureaucrat.executeForm(*form);
	// makeForm は new した書類を返すので、解放は呼び出し側の責任
	delete form;
	std::cout << std::endl;
}

static void	knownFormsTest(void)
{
	std::cout << "=== 存在する 3 種類の書類 ===" << std::endl;

	Intern		intern;
	Bureaucrat	boss("Boss", 1);

	std::cout << std::endl;
	runForm(intern, boss, "shrubbery creation", "home");
	runForm(intern, boss, "robotomy request", "Bender");
	runForm(intern, boss, "presidential pardon", "Arthur Dent");
}

static void	unknownFormTest(void)
{
	std::cout << "=== 存在しない書類名 ===" << std::endl;

	Intern		intern;
	Bureaucrat	boss("Boss", 1);

	std::cout << std::endl;
	runForm(intern, boss, "coffee making", "office");
	runForm(intern, boss, "", "nothing");
}

static void	subjectExampleTest(void)
{
	std::cout << "=== 課題文の例 ===" << std::endl;

	Intern	someRandomIntern;
	AForm	*rrf;

	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	if (rrf != NULL)
	{
		std::cout << *rrf << std::endl;
		delete rrf;
	}
	std::cout << std::endl;
}

int	main(void)
{
	knownFormsTest();
	unknownFormTest();
	subjectExampleTest();
	return (0);
}
