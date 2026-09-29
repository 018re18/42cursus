#include "ShrubberyCreationForm.hpp"

#include <fstream>

// -------------------------------- 正準形 ----------------------------------

ShrubberyCreationForm::ShrubberyCreationForm(void)
	: AForm("ShrubberyCreationForm", 145, 137), _target("default")
{
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
	std::cout << "ShrubberyCreationForm constructor called for " << this->_target << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src)
	: AForm(src), _target(src._target)
{
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}

// _target は const なので、基底クラス側 (署名状態) の代入だけを行う。
ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &rhs)
{
	std::cout << "ShrubberyCreationForm copy assignment operator called" << std::endl;
	if (this != &rhs)
		AForm::operator=(rhs);
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

// -------------------------------- ゲッター --------------------------------

std::string const	&ShrubberyCreationForm::getTarget(void) const
{
	return (this->_target);
}

// -------------------------------- 実処理 ----------------------------------

// 署名と等級の確認は AForm::execute() が済ませているので、ここは木を植えるだけ。
void	ShrubberyCreationForm::_executeAction(void) const
{
	std::string		filename = this->_target + "_shrubbery";
	std::ofstream	ofs(filename.c_str());

	if (!ofs.is_open())
		throw ShrubberyCreationForm::FileCreationFailedException();
	ofs << "       ###\n"
		<< "      #o###\n"
		<< "    #####o###\n"
		<< "   #o#\\#|#/###\n"
		<< "    ###\\|/#o#\n"
		<< "     # }|{  #\n"
		<< "       }|{\n"
		<< "\n"
		<< "         ###\n"
		<< "        #####\n"
		<< "       ###o###\n"
		<< "      #o#####o#\n"
		<< "     ####\\|/####\n"
		<< "        }|{\n"
		<< "        }|{\n";
	ofs.close();
	// close 後に書き込みエラーが出ていないかも確認する
	if (ofs.fail())
		throw ShrubberyCreationForm::FileCreationFailedException();
	std::cout << "ShrubberyCreationForm: " << filename << " に木を植えました" << std::endl;
}

// -------------------------------- 例外 ------------------------------------

char const	*ShrubberyCreationForm::FileCreationFailedException::what(void) const throw()
{
	return ("ShrubberyCreationForm::FileCreationFailedException: cannot create the file");
}
