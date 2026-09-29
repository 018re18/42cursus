#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Array.hpp"

#define MAX_VAL 750

// 配布された main の内容 (srand / rand / time 用の include だけ補った)
static int	subjectTest(void)
{
	Array<int>	numbers(MAX_VAL);
	int			*mirror = new int[MAX_VAL];

	srand(time(NULL));
	for (int i = 0; i < MAX_VAL; i++)
	{
		const int	value = rand();
		numbers[i] = value;
		mirror[i] = value;
	}
	//SCOPE
	{
		Array<int>	tmp = numbers;
		Array<int>	test(tmp);
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		if (mirror[i] != numbers[i])
		{
			std::cerr << "didn't save the same value!!" << std::endl;
			delete[] mirror;
			return (1);
		}
	}
	try
	{
		numbers[-2] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		numbers[MAX_VAL] = 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	for (int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand();
	}
	delete[] mirror;
	return (0);
}

template <typename T>
static void	printArray(std::string const &label, Array<T> const &arr)
{
	std::cout << label << " (size " << arr.size() << "): ";
	for (unsigned int i = 0; i < arr.size(); i++)
		std::cout << "[" << arr[i] << "] ";
	std::cout << std::endl;
}

static void	defaultInitTest(void)
{
	std::cout << "=== default initialization ===" << std::endl;
	int	*a = new int();

	std::cout << "new int() -> " << *a << std::endl;
	delete a;

	Array<int>			ints(5);
	Array<std::string>	strs(3);

	printArray("Array<int>(5)", ints);
	printArray("Array<std::string>(3)", strs);
}

static void	emptyArrayTest(void)
{
	std::cout << "=== empty array ===" << std::endl;
	Array<int>	empty;

	std::cout << "size = " << empty.size() << std::endl;
	try
	{
		empty[0] = 42;
		std::cout << "no exception (NG)" << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << "caught: " << e.what() << std::endl;
	}
}

static void	copyTest(void)
{
	std::cout << "=== copy constructor ===" << std::endl;
	Array<int>	orig(3);

	for (unsigned int i = 0; i < orig.size(); i++)
		orig[i] = i + 1;
	Array<int>	copy(orig);

	copy[0] = 100;
	orig[2] = 300;
	printArray("orig", orig);
	printArray("copy", copy);
}

static void	assignmentTest(void)
{
	std::cout << "=== assignment operator ===" << std::endl;
	Array<std::string>	a(2);
	Array<std::string>	b(5);

	a[0] = "foo";
	a[1] = "bar";
	b = a;
	b[0] = "changed";
	printArray("a", a);
	printArray("b", b);

	// b = b; と直接書くと -Wself-assign-overloaded で弾かれるので参照経由で自己代入する
	Array<std::string>	&ref = b;

	b = ref;
	printArray("b after self-assignment", b);

	Array<std::string>	empty;

	b = empty;
	printArray("b after b = empty", b);
}

static void	constTest(void)
{
	std::cout << "=== const array ===" << std::endl;
	Array<int>	src(3);

	src[1] = 7;
	Array<int> const	c(src);

	std::cout << "c[1] = " << c[1] << ", c.size() = " << c.size() << std::endl;
	// c[1] = 0; // const なのでコンパイルエラーになる
	try
	{
		std::cout << c[3] << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << "caught: " << e.what() << std::endl;
	}
}

static void	tryAccess(Array<int> &arr, long index)
{
	std::cout << "arr[" << index << "] -> ";
	try
	{
		std::cout << arr[index] << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << "caught: " << e.what() << std::endl;
	}
}

static void	boundsTest(void)
{
	std::cout << "=== bounds (size 3) ===" << std::endl;
	Array<int>	arr(3);

	arr[0] = 10;
	arr[2] = 30;
	tryAccess(arr, 0);
	tryAccess(arr, 2);
	tryAccess(arr, 3);
	tryAccess(arr, -1);
	tryAccess(arr, 4294967295L);	// UINT_MAX
	tryAccess(arr, 4294967296L);	// 2^32: unsigned int だと 0 に切り詰められてしまう値
	std::cout << "after errors: [" << arr[0] << "] [" << arr[1] << "] [" << arr[2] << "]" << std::endl;
}

// 指定した回数目の代入で例外を投げる型 (コピー途中で失敗したときの挙動確認用)
struct Fragile
{
	static int	alive;
	static int	throwAt;
	int			v;

	Fragile(void) : v(0) { alive++; }
	Fragile(Fragile const &o) : v(o.v) { alive++; }
	~Fragile(void) { alive--; }
	Fragile	&operator=(Fragile const &o)
	{
		if (throwAt >= 0 && throwAt-- == 0)
			throw std::runtime_error("Fragile: copy failed");
		v = o.v;
		return (*this);
	}
};
int	Fragile::alive = 0;
int	Fragile::throwAt = -1;

static void	exceptionSafetyTest(void)
{
	std::cout << "=== exception safety (T throws while copying) ===" << std::endl;
	{
		Array<Fragile>	src(5);
		Array<Fragile>	dst(2);

		dst[0].v = 1;
		dst[1].v = 2;
		Fragile::throwAt = 2;
		try
		{
			dst = src;
		}
		catch (std::exception const &e)
		{
			std::cout << "caught: " << e.what() << std::endl;
		}
		std::cout << "dst unchanged: size " << dst.size()
			<< " [" << dst[0].v << "] [" << dst[1].v << "]" << std::endl;

		Fragile::throwAt = 2;
		try
		{
			Array<Fragile>	copy(src);
		}
		catch (std::exception const &e)
		{
			std::cout << "caught: " << e.what() << std::endl;
		}
		Fragile::throwAt = -1;
		std::cout << "alive objects: " << Fragile::alive << " (expected 7)" << std::endl;
	}
	std::cout << "alive objects after scope: " << Fragile::alive << " (expected 0)" << std::endl;
}

int	main(void)
{
	std::cout << "=== subject test ===" << std::endl;
	if (subjectTest() != 0)
		return (1);
	defaultInitTest();
	emptyArrayTest();
	copyTest();
	assignmentTest();
	constTest();
	boundsTest();
	exceptionSafetyTest();
	return (0);
}
