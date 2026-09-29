#include <iostream>
#include <string>

#include "iter.hpp"

// 読むだけの関数テンプレート (const 参照で受け取る)
template <typename T>
void	print(T const &x)
{
	std::cout << "[" << x << "] ";
}

// 要素を書き換える関数テンプレート (非 const 参照で受け取る)
template <typename T>
void	increment(T &x)
{
	x++;
}

// 普通の (テンプレートでない) 関数
void	toUpperFirst(std::string &s)
{
	if (!s.empty() && s[0] >= 'a' && s[0] <= 'z')
		s[0] = s[0] - 'a' + 'A';
}

// operator() を持つ関数オブジェクト (渡された値を *total に足していく)
class Sum
{
	public:
		Sum(void) : _total(NULL) {}
		Sum(int *total) : _total(total) {}
		Sum(Sum const &src) : _total(src._total) {}
		Sum	&operator=(Sum const &rhs)
		{
			_total = rhs._total;
			return (*this);
		}
		~Sum(void) {}

		void	operator()(int const &x) const
		{
			if (_total != NULL)
				*_total += x;
		}

	private:
		int	*_total;
};

int	main(void)
{
	std::cout << "=== int array (non-const) ===" << std::endl;
	int	nums[] = {1, 2, 3, 4, 5};

	::iter(nums, 5, print<int>);
	std::cout << std::endl;
	::iter(nums, 5, increment<int>);
	::iter(nums, 5, print<int>);
	std::cout << std::endl;

	std::cout << "=== const int array ===" << std::endl;
	int const	cnums[] = {10, 20, 30};

	::iter(cnums, 3, print<int>);
	std::cout << std::endl;
	// ::iter(cnums, 3, increment<int>); // const を書き換えようとするのでコンパイルエラーになる

	std::cout << "=== std::string array ===" << std::endl;
	std::string	strs[] = {"hello", "world", "cpp07"};

	::iter(strs, 3, toUpperFirst);
	::iter(strs, 3, print<std::string>);
	std::cout << std::endl;

	std::cout << "=== double array ===" << std::endl;
	double	dbls[] = {0.5, 1.5, 2.5};

	::iter(dbls, 3, increment<double>);
	::iter(dbls, 3, print<double>);
	std::cout << std::endl;

	std::cout << "=== functor ===" << std::endl;
	int	total = 0;

	::iter(nums, 5, Sum(&total));
	std::cout << "sum = " << total << std::endl;

	std::cout << "=== non-const array + const-ref func (print<const int>) ===" << std::endl;
	::iter(nums, 5, print<const int>);
	std::cout << std::endl;

	std::cout << "=== const std::string array ===" << std::endl;
	std::string const	cstrs[] = {"abc", "", "xyz"};

	::iter(cstrs, 3, print<std::string>);
	std::cout << std::endl;

	std::cout << "=== partial length (first 2 of 5) ===" << std::endl;
	::iter(nums, 2, print<int>);
	std::cout << std::endl;

	std::cout << "=== length 0 / NULL ===" << std::endl;
	::iter(nums, 0, print<int>);
	::iter(static_cast<int *>(NULL), 5, print<int>);
	std::cout << "(nothing printed)" << std::endl;
	return (0);
}
