#ifndef INTERN_HPP
# define INTERN_HPP

#include <string>

class AForm;

// インターン。名前も等級も持たず、書類を作る仕事だけをする。
//
// makeForm は if/else の羅列を避けるため、「名前」と「生成関数」の対応表を
// 一度だけ用意しておき、ループで引き当てる方式にしている。
// 書類の種類が増えても、表に 1 行足すだけで済む。
class Intern
{
	private:
		// 書類名と、その書類を生成する関数の組
		struct FormEntry
		{
			char const	*name;
			AForm		*(*create)(std::string const &target);
		};

		static FormEntry const	_forms[];
		static int const		_formCount;

		// 対応表に載せる生成関数
		static AForm	*_createShrubberyCreationForm(std::string const &target);
		static AForm	*_createRobotomyRequestForm(std::string const &target);
		static AForm	*_createPresidentialPardonForm(std::string const &target);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Intern(void);
		Intern(Intern const &src);
		Intern &operator=(Intern const &rhs);
		~Intern(void);

		// 該当する書類がなければエラーを表示して NULL を返す
		AForm	*makeForm(std::string const &formName, std::string const &target) const;
};

#endif
