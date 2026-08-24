#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>
#include <string>

// 決まった数の「考え」を持つ脳。
// Cat と Dog が new で 1 つずつ持ち、コピーのときは中身ごと複製する
// (ディープコピー) 必要がある。
class Brain
{
	private:
		static const int	_size = 100;

		std::string	ideas[_size];

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Brain(void);
		Brain(Brain const &src);
		Brain &operator=(Brain const &rhs);
		~Brain(void);

		// index が範囲外なら、setIdea は何もせず getIdea は代わりの文字列を返す
		void				setIdea(int index, std::string const &idea);
		std::string const	&getIdea(int index) const;
};

#endif
