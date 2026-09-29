#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

// 実行すると <target>_shrubbery というファイルを作り、ASCII アートの木を書き込む。
// 署名 145 / 実行 137。
class ShrubberyCreationForm : public AForm
{
	private:
		std::string const	_target;

	protected:
		virtual void	_executeAction(void) const;

	public:
		// ファイルを作れなかったときに投げる。黙って戻ると executeForm が
		// 「executed」と成功を報告してしまい、実際と食い違うため。
		class FileCreationFailedException : public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};

		// 直交正準形 (Orthodox Canonical Form)
		ShrubberyCreationForm(void);
		ShrubberyCreationForm(ShrubberyCreationForm const &src);
		ShrubberyCreationForm &operator=(ShrubberyCreationForm const &rhs);
		virtual ~ShrubberyCreationForm(void);

		// 課題の指定どおり、引数は対象だけ
		ShrubberyCreationForm(std::string const &target);

		std::string const	&getTarget(void) const;
};

#endif
