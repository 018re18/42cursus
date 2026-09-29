#ifndef EASYFIND_TPP
# define EASYFIND_TPP

#include <algorithm>
#include <stdexcept>

// T::iterator は「型」だとコンパイラに教えるため typename が必要 (依存名)
template <typename T>
typename T::iterator	easyfind(T &container, int value)
{
	typename T::iterator	it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
		throw std::runtime_error("easyfind: value not found");
	return (it);
}

template <typename T>
typename T::const_iterator	easyfind(T const &container, int value)
{
	typename T::const_iterator	it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
		throw std::runtime_error("easyfind: value not found");
	return (it);
}

#endif
