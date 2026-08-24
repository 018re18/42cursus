#include "Brain.hpp"

// -------------------------------- 正準形 ----------------------------------

Brain::Brain(void)
{
	for (int i = 0; i < Brain::_size; i++)
		this->ideas[i] = "...";
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(Brain const &src)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = src;
}

// 配列の要素を 1 つずつ写す。これが Cat / Dog のディープコピーの中身になる。
Brain &Brain::operator=(Brain const &rhs)
{
	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		for (int i = 0; i < Brain::_size; i++)
			this->ideas[i] = rhs.ideas[i];
	}
	return (*this);
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor called" << std::endl;
}

// -------------------------------- 考え -------------------------------------

void	Brain::setIdea(int index, std::string const &idea)
{
	if (index < 0 || index >= Brain::_size)
	{
		std::cout << "Brain: idea index " << index << " is out of range"
			<< std::endl;
		return ;
	}
	this->ideas[index] = idea;
}

// 参照を返す約束なので、範囲外のときも実体のある文字列を返す必要がある。
// そのために寿命がプログラム全体に及ぶ static な文字列を用意している。
std::string const	&Brain::getIdea(int index) const
{
	static const std::string	nothing = "(no such idea)";

	if (index < 0 || index >= Brain::_size)
		return (nothing);
	return (this->ideas[index]);
}
