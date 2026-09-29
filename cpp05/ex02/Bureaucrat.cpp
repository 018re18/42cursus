#include "Bureaucrat.hpp"
#include "AForm.hpp"

// 等級定数の定義。クラス内の初期化子だけでは参照を束縛する用途
// (std::min に渡す等の ODR 使用) でリンクできないため、ここに実体を置く。
int const	Bureaucrat::HighestGrade;
int const	Bureaucrat::LowestGrade;

// -------------------------------- 正準形 ----------------------------------

Bureaucrat::Bureaucrat(void) : _name("default"), _grade(LowestGrade)
{
	std::cout << "Bureaucrat default constructor called" << std::endl;
}

// メンバ初期化子リストで _name を初期化してから本体で検査する。
// ここで例外を投げると、構築途中のオブジェクトは生成されず、
// 初期化済みのメンバだけがきれいに破棄される (デストラクタは呼ばれない)。
Bureaucrat::Bureaucrat(std::string const &name, int grade) : _name(name), _grade(grade)
{
	_checkGrade(grade);
	std::cout << "Bureaucrat constructor called for " << this->_name << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &src) : _name(src._name), _grade(src._grade)
{
	std::cout << "Bureaucrat copy constructor called" << std::endl;
}

// _name は const なので代入できない。等級だけをコピーする。
Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rhs)
{
	std::cout << "Bureaucrat copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_grade = rhs._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << "Bureaucrat destructor called for " << this->_name << std::endl;
}

// -------------------------------- 等級の検査 ------------------------------

void	Bureaucrat::_checkGrade(int grade)
{
	if (grade < HighestGrade)
		throw Bureaucrat::GradeTooHighException();
	if (grade > LowestGrade)
		throw Bureaucrat::GradeTooLowException();
}

// -------------------------------- ゲッター --------------------------------

std::string const	&Bureaucrat::getName(void) const
{
	return (this->_name);
}

int	Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}

// -------------------------------- 昇格・降格 ------------------------------

// 1 が最上位なので、昇格 = 値を 1 減らす。
// 先に検査してから代入するので、例外が飛んでも状態は変わらない (強い例外保証)。
void	Bureaucrat::incrementGrade(void)
{
	_checkGrade(this->_grade - 1);
	this->_grade--;
}

void	Bureaucrat::decrementGrade(void)
{
	_checkGrade(this->_grade + 1);
	this->_grade++;
}

// -------------------------------- 署名と実行 ------------------------------

// 判定はすべて AForm 側に任せ、ここでは結果の報告だけを担当する。
void	Bureaucrat::signForm(AForm &form) const
{
	try
	{
		form.beSigned(*this);
		std::cout << this->_name << " signed " << form.getName() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << this->_name << " couldn't sign " << form.getName()
			<< " because " << e.what() << "." << std::endl;
	}
}

void	Bureaucrat::executeForm(AForm const &form) const
{
	try
	{
		form.execute(*this);
		std::cout << this->_name << " executed " << form.getName() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << this->_name << " couldn't execute " << form.getName()
			<< " because " << e.what() << "." << std::endl;
	}
}

// -------------------------------- 例外 ------------------------------------

char const	*Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Bureaucrat::GradeTooHighException: grade is too high");
}

char const	*Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Bureaucrat::GradeTooLowException: grade is too low");
}

// -------------------------------- 出力 ------------------------------------

std::ostream	&operator<<(std::ostream &os, Bureaucrat const &rhs)
{
	os << rhs.getName() << ", bureaucrat grade " << rhs.getGrade() << ".";
	return (os);
}
