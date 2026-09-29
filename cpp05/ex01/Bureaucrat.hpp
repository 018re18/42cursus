#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <exception>
#include <iostream>
#include <string>

class Form;

// 官僚。名前は const で、等級 (grade) は 1 (最上位) 〜 150 (最下位)。
// 範囲外の等級になる操作はすべて例外を投げる。
class Bureaucrat
{
	public:
		// 等級の上限・下限。数字が小さいほど「偉い」ことに注意
		static int const	HighestGrade = 1;
		static int const	LowestGrade = 150;

	private:
		std::string const	_name;
		int					_grade;

		// 等級が範囲内かを検査し、外れていれば例外を投げる
		static void	_checkGrade(int grade);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Bureaucrat(void);
		Bureaucrat(Bureaucrat const &src);
		Bureaucrat &operator=(Bureaucrat const &rhs);
		~Bureaucrat(void);

		Bureaucrat(std::string const &name, int grade);

		std::string const	&getName(void) const;
		int					getGrade(void) const;

		// grade 1 が最上位なので、昇格は等級の値を 1 減らす操作になる
		void	incrementGrade(void);
		void	decrementGrade(void);

		// 書類への署名を試み、結果をそのまま標準出力に報告する
		void	signForm(Form &form) const;

		// 例外クラスは正準形でなくてよい、と課題文に明記されている
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

std::ostream	&operator<<(std::ostream &os, Bureaucrat const &rhs);

#endif
