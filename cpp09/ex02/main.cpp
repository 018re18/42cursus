#include "PmergeMe.hpp"

#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <vector>

// 経過した CPU 時間をマイクロ秒で返す
static double	elapsedMicroseconds(std::clock_t start, std::clock_t end)
{
	return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

template <typename Container>
static void	printContainer(Container const &container)
{
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << ' ' << *it;
}

int	main(int argc, char **argv)
{
	PmergeMe					sorter;
	std::vector<unsigned int>	unsorted;
	double						vectorTime;
	double						dequeTime;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		// 入力の検証と "Before:" 表示用に、計測の外で一度解析しておく。
		// 不正な入力はここで弾かれるので、エラー時は何も表示せずに終われる
		sorter.loadVector(argc - 1, argv + 1);
		unsorted = sorter.getVector();

		// 計測には、引数を解析してコンテナに格納する処理 (データ管理) とソートの両方を含める
		std::clock_t	start = std::clock();
		sorter.loadVector(argc - 1, argv + 1);
		sorter.sortVector();
		vectorTime = elapsedMicroseconds(start, std::clock());

		start = std::clock();
		sorter.loadDeque(argc - 1, argv + 1);
		sorter.sortDeque();
		dequeTime = elapsedMicroseconds(start, std::clock());
	}
	catch (std::exception const &e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::size_t const	size = unsorted.size();

	std::cout << "Before:";
	printContainer(unsorted);
	std::cout << std::endl;
	std::cout << "After:";
	printContainer(sorter.getVector());
	std::cout << std::endl;
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << size
		<< " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << size
		<< " elements with std::deque  : " << dequeTime << " us" << std::endl;
	return (0);
}
