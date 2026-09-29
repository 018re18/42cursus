#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

#include "Span.hpp"

// 課題の PDF にある例。2 と 14 が出力されるはず
static void	subjectTest(void)
{
	std::cout << "=== subject test ===" << std::endl;
	Span	sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

static void	exceptionTest(void)
{
	std::cout << "=== exceptions ===" << std::endl;
	Span	sp(2);

	try
	{
		sp.shortestSpan();
	}
	catch (std::exception const &e)
	{
		std::cout << "empty shortestSpan: " << e.what() << std::endl;
	}
	sp.addNumber(1);
	try
	{
		sp.longestSpan();
	}
	catch (std::exception const &e)
	{
		std::cout << "one element longestSpan: " << e.what() << std::endl;
	}
	sp.addNumber(2);
	try
	{
		sp.addNumber(3);
	}
	catch (std::exception const &e)
	{
		std::cout << "addNumber to full span: " << e.what() << std::endl;
	}

	Span	zero(0);
	try
	{
		zero.addNumber(0);
	}
	catch (std::exception const &e)
	{
		std::cout << "addNumber to Span(0): " << e.what() << std::endl;
	}
}

// int の差がオーバーフローするような値でも正しく計算できるか
static void	extremeTest(void)
{
	std::cout << "=== INT_MIN / INT_MAX ===" << std::endl;
	Span	sp(3);

	sp.addNumber(INT_MAX);
	sp.addNumber(INT_MIN);
	std::cout << "shortest: " << sp.shortestSpan() << " (expected 4294967295)" << std::endl;
	std::cout << "longest:  " << sp.longestSpan() << " (expected 4294967295)" << std::endl;
	sp.addNumber(INT_MAX);
	std::cout << "after adding INT_MAX again, shortest: " << sp.shortestSpan()
		<< " (expected 0)" << std::endl;
}

static void	rangeTest(void)
{
	std::cout << "=== addRange ===" << std::endl;
	std::vector<int>	v;
	std::list<int>		l;

	for (int i = 0; i < 5; i++)
		v.push_back(i * i);			// 0 1 4 9 16
	l.push_back(100);
	l.push_back(-100);

	Span	sp(7);
	sp.addRange(v.begin(), v.end());
	sp.addRange(l.begin(), l.end());
	std::cout << "size: " << sp.size() << "/" << sp.maxSize() << std::endl;
	std::cout << "shortest: " << sp.shortestSpan() << " (expected 1)" << std::endl;
	std::cout << "longest:  " << sp.longestSpan() << " (expected 200)" << std::endl;

	// 普通の配列のポインタもイテレータとして使える
	int		arr[] = {10, 20, 30};
	Span	small(2);
	try
	{
		small.addRange(arr, arr + 3);
	}
	catch (std::exception const &e)
	{
		std::cout << "addRange over capacity: " << e.what() << std::endl;
	}
	// 失敗したときは 1 つも追加されていないはず
	std::cout << "size after failed addRange: " << small.size() << " (expected 0)" << std::endl;
	// ちょうど満杯になる範囲は成功する
	small.addRange(arr, arr + 2);
	std::cout << "size after addRange of 2: " << small.size() << "/" << small.maxSize() << std::endl;
	// 満杯でも、空の範囲なら何も起きない
	small.addRange(arr, arr);
	std::cout << "size after empty addRange: " << small.size() << "/" << small.maxSize() << std::endl;
}

// N は unsigned int の最大値まで受け付ける。
// (コンストラクタで N 個分を確保していないので、大きな N でも bad_alloc にならない)
static void	hugeCapacityTest(void)
{
	std::cout << "=== Span(UINT_MAX) ===" << std::endl;
	Span	sp(UINT_MAX);

	sp.addNumber(1);
	sp.addNumber(5);
	std::cout << "size: " << sp.size() << "/" << sp.maxSize() << std::endl;
	std::cout << "longest: " << sp.longestSpan() << " (expected 4)" << std::endl;
}

static void	copyTest(void)
{
	std::cout << "=== copy ===" << std::endl;
	Span	a(3);

	a.addNumber(1);
	a.addNumber(10);

	Span	b(a);
	Span	c;
	c = a;
	a.addNumber(2);		// a だけ変更し、b, c に影響しないことを確認する
	std::cout << "a shortest: " << a.shortestSpan() << " (expected 1)" << std::endl;
	std::cout << "b shortest: " << b.shortestSpan() << " (expected 9)" << std::endl;
	std::cout << "c shortest: " << c.shortestSpan() << " (expected 9)" << std::endl;
	b.addNumber(5);
	std::cout << "b size after addNumber: " << b.size() << "/" << b.maxSize() << std::endl;
}

// 総当たり O(n^2) で求めた答えと比較し、実装が正しいか確認する
static void	bigTest(unsigned int n, bool bruteForce)
{
	std::cout << "=== " << n << " random numbers ===" << std::endl;
	std::vector<int>	numbers;

	for (unsigned int i = 0; i < n; i++)
		numbers.push_back(rand() - RAND_MAX / 2);

	Span	sp(n);
	sp.addRange(numbers.begin(), numbers.end());
	unsigned int	shortest = sp.shortestSpan();
	unsigned int	longest = sp.longestSpan();
	std::cout << "shortest: " << shortest << std::endl;
	std::cout << "longest:  " << longest << std::endl;

	if (!bruteForce)
		return ;
	unsigned int	expShortest = UINT_MAX;
	unsigned int	expLongest = 0;
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = i + 1; j < n; j++)
		{
			int				lo = std::min(numbers[i], numbers[j]);
			int				hi = std::max(numbers[i], numbers[j]);
			unsigned int	d = static_cast<unsigned int>(hi) - static_cast<unsigned int>(lo);
			if (d < expShortest)
				expShortest = d;
			if (d > expLongest)
				expLongest = d;
		}
	}
	std::cout << "brute force check: "
		<< ((shortest == expShortest && longest == expLongest) ? "OK" : "KO") << std::endl;
}

int	main(void)
{
	srand(time(NULL));
	// 想定外の例外 (大量確保時の std::bad_alloc など) で terminate しないよう、全体を囲っておく
	try
	{
		subjectTest();
		exceptionTest();
		extremeTest();
		rangeTest();
		hugeCapacityTest();
		copyTest();
		bigTest(10000, true);
		bigTest(1000000, false);
	}
	catch (std::exception const &e)
	{
		std::cerr << "unexpected exception: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
