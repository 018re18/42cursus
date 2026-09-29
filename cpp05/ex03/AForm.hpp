#ifndef AFORM_HPP
# define AFORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

// 書類の抽象基底クラス。
// 属性は基底クラスの private のままにし、派生クラスは getter 経由で参照する。
//
// execute() は「署名済みか」「実行者の等級は足りるか」の共通チェックだけを行い、
// 実際の処理は純粋仮想の _executeAction() に委ねる (Template Method)。
// こうすればチェックの重複がなくなり、派生クラスは処理だけを書けばよい。
class AForm
{
	private:
		std::string const	_name;
		bool				_isSigned;
		int const			_gradeToSign;
		int const			_gradeToExecute;

		static void	_checkGrade(int grade);

	protected:
		// 派生クラスが実装する実処理。execute() からのみ呼ばれる
		virtual void	_executeAction(void) const = 0;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		AForm(void);
		AForm(AForm const &src);
		AForm &operator=(AForm const &rhs);
		// 基底クラスのポインタ越しに delete されるので virtual
		virtual ~AForm(void);

		AForm(std::string const &name, int gradeToSign, int gradeToExecute);

		std::string const	&getName(void) const;
		bool				getIsSigned(void) const;
		int					getGradeToSign(void) const;
		int					getGradeToExecute(void) const;

		void	beSigned(Bureaucrat const &bureaucrat);
		void	execute(Bureaucrat const &executor) const;

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

		class FormNotSignedException : public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};
};

std::ostream	&operator<<(std::ostream &os, AForm const &rhs);

#endif
