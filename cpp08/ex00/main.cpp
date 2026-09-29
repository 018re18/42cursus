#include <climits>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#include "easyfind.hpp"

// value を探して、見つかった位置 (先頭からの距離) か例外メッセージを表示する
template <typename T>
static void	tryFind(std::string const &label, T &container, int value)
{
	std::cout << label << " find " << value << ": ";
	try
	{
		typename T::iterator	it = easyfind(container, value);

		std::cout << "found " << *it << " at index "
			<< std::distance(container.begin(), it) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}
}

static void	vectorTest(void)
{
	std::cout << "=== std::vector ===" << std::endl;
	std::vector<int>	v;

	for (int i = 0; i < 10; i++)
		v.push_back(i * 10);
	tryFind("vector", v, 0);
	tryFind("vector", v, 50);
	tryFind("vector", v, 90);
	tryFind("vector", v, 42);
	tryFind("vector", v, -10);
}

static void	listTest(void)
{
	std::cout << "=== std::list ===" << std::endl;
	std::list<int>	l;

	l.push_back(3);
	l.push_back(1);
	l.push_back(4);
	l.push_back(1);
	l.push_back(5);
	// 1 は 2 回出てくるが、最初の位置 (index 1) が返るはず
	tryFind("list", l, 1);
	tryFind("list", l, 5);
	tryFind("list", l, 9);
}

static void	dequeTest(void)
{
	std::cout << "=== std::deque ===" << std::endl;
	std::deque<int>	d;

	d.push_back(INT_MIN);
	d.push_back(0);
	d.push_back(INT_MAX);
	tryFind("deque", d, INT_MIN);
	tryFind("deque", d, INT_MAX);
	tryFind("deque", d, 1);
}

static void	emptyTest(void)
{
	std::cout << "=== empty container ===" << std::endl;
	std::vector<int>	empty;

	tryFind("empty vector", empty, 0);
}

// 返ってきたイテレータ経由で、コンテナ内の要素を書き換えられることを確認する
static void	modifyTest(void)
{
	std::cout << "=== modify through iterator ===" << std::endl;
	std::vector<int>	v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	*easyfind(v, 2) = 42;
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

static void	constTest(void)
{
	std::cout << "=== const container ===" << std::endl;
	std::vector<int>		tmp;

	tmp.push_back(7);
	tmp.push_back(8);
	std::vector<int> const	cv(tmp);

	try
	{
		std::vector<int>::const_iterator	it = easyfind(cv, 8);

		std::cout << "const vector find 8: found " << *it << std::endl;
		easyfind(cv, 9);
	}
	catch (std::exception const &e)
	{
		std::cout << "const vector find 9: " << e.what() << std::endl;
	}
}

int	main(void)
{
	vectorTest();
	listTest();
	dequeTest();
	emptyTest();
	modifyTest();
	constTest();
	return (0);
}
