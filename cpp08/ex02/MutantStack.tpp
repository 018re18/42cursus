#ifndef MUTANTSTACK_TPP
# define MUTANTSTACK_TPP

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack(void) : std::stack<T, Container>()
{
}

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack(MutantStack const &src) : std::stack<T, Container>(src)
{
}

template <typename T, typename Container>
MutantStack<T, Container>	&MutantStack<T, Container>::operator=(MutantStack const &rhs)
{
	if (this != &rhs)
		std::stack<T, Container>::operator=(rhs);
	return (*this);
}

template <typename T, typename Container>
MutantStack<T, Container>::~MutantStack(void)
{
}

// c は基底クラス (テンプレート) のメンバなので、this-> を付けないと名前が見つからない
template <typename T, typename Container>
typename MutantStack<T, Container>::iterator	MutantStack<T, Container>::begin(void)
{
	return (this->c.begin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::iterator	MutantStack<T, Container>::end(void)
{
	return (this->c.end());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator	MutantStack<T, Container>::begin(void) const
{
	return (this->c.begin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator	MutantStack<T, Container>::end(void) const
{
	return (this->c.end());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator	MutantStack<T, Container>::rbegin(void)
{
	return (this->c.rbegin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator	MutantStack<T, Container>::rend(void)
{
	return (this->c.rend());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator	MutantStack<T, Container>::rbegin(void) const
{
	return (this->c.rbegin());
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator	MutantStack<T, Container>::rend(void) const
{
	return (this->c.rend());
}

#endif
