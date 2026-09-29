#ifndef FORM_HPP
# define FORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

// 書類。名前・署名に必要な等級・実行に必要な等級はすべて const で、
// 変わるのは「署名済みかどうか」だけ。属性はすべて private。
class Form
{
	private:
		std::string const	_name;
		bool				_isSigned;
		int const			_gradeToSign;
		int const			_gradeToExecute;

		static void	_checkGrade(int grade);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Form(void);
		Form(Form const &src);
		Form &operator=(Form const &rhs);
		~Form(void);

		Form(std::string const &name, int gradeToSign, int gradeToExecute);

		std::string const	&getName(void) const;
		bool				getIsSigned(void) const;
		int					getGradeToSign(void) const;
		int					getGradeToExecute(void) const;

		// 官僚の等級が足りていれば署名済みにする。足りなければ例外
		void	beSigned(Bureaucrat const &bureaucrat);

		class GradeTooHighException : public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};
};

std::ostream	&operator<<(std::ostream &os, Form const &rhs);

#endif
