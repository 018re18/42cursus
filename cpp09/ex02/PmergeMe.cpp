#include "PmergeMe.hpp"

#include <algorithm>
#include <cctype>
#include <climits>
#include <sstream>
#include <stdexcept>

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(PmergeMe const &src)
	: _vector(src._vector), _deque(src._deque)
{
}

PmergeMe	&PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		this->_vector = rhs._vector;
		this->_deque = rhs._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
}

std::vector<unsigned int> const	&PmergeMe::getVector(void) const
{
	return (this->_vector);
}

std::deque<unsigned int> const	&PmergeMe::getDeque(void) const
{
	return (this->_deque);
}

// 数字だけからなる 1 以上 INT_MAX 以下の整数を受け付ける。
// "-1" や "+1", "0", "1a" などはすべてエラー
unsigned int	PmergeMe::_parseNumber(std::string const &token)
{
	int	value = 0;

	if (token.empty())
		throw std::runtime_error("empty number");
	for (std::string::size_type i = 0; i < token.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			throw std::runtime_error("not a positive integer: " + token);

		int const	digit = token[i] - '0';

		// 掛け算・足し算の前に確認し、計算途中でも INT_MAX を超えないようにする
		if (value > (INT_MAX - digit) / 10)
			throw std::runtime_error("number too large: " + token);
		value = value * 10 + digit;
	}
	if (value == 0)
		throw std::runtime_error("not a positive integer: " + token);
	return (static_cast<unsigned int>(value));
}

// 1 つの引数に空白区切りで複数の数が入っていても受け付ける ("3 5 9" など)。
// 数を 1 つも含まない引数 ("" や "  ") はエラーにする
void	PmergeMe::loadVector(int argc, char **argv)
{
	this->_vector.clear();
	for (int i = 0; i < argc; ++i)
	{
		std::istringstream	iss(argv[i]);
		std::string			token;
		bool				found = false;

		while (iss >> token)
		{
			this->_vector.push_back(_parseNumber(token));
			found = true;
		}
		if (!found)
			throw std::runtime_error("empty argument");
	}
	if (this->_vector.empty())
		throw std::runtime_error("no numbers");
}

void	PmergeMe::loadDeque(int argc, char **argv)
{
	this->_deque.clear();
	for (int i = 0; i < argc; ++i)
	{
		std::istringstream	iss(argv[i]);
		std::string			token;
		bool				found = false;

		while (iss >> token)
		{
			this->_deque.push_back(_parseNumber(token));
			found = true;
		}
		if (!found)
			throw std::runtime_error("empty argument");
	}
	if (this->_deque.empty())
		throw std::runtime_error("no numbers");
}

/*
** Ford-Johnson アルゴリズムの流れ (n 個の要素)
**  1. 隣り合う 2 つずつを組にし、各組の大きい方 (a) と小さい方 (b) に分ける。
**     n が奇数なら最後の 1 つは組にならず余る。
**  2. a の列だけを再帰的に同じアルゴリズムでソートし、これを主鎖 (main chain) とする。
**     ソート後の順に a1 <= a2 <= ... と呼び、それぞれの相方を b1, b2, ... とする。
**  3. b1 <= a1 なので、b1 は比較なしで主鎖の先頭に置ける。
**  4. 残りの b をヤコブスタール数で区切ったグループ順に挿入する:
**       b3, b2, b5, b4, b11, b10, ..., b6, b21, ...
**     bk は ak より前にあると分かっているので、主鎖の「ak の手前まで」を二分探索すればよい。
**     この順序だと、各グループの探索範囲の長さが 2^k - 1 以下に収まり、比較回数が最小に近くなる。
**     余りの要素は相方がいないので、主鎖全体を二分探索する。
**
** 値に重複があっても相方の対応が崩れないよう、値そのものではなく
** keys 内の添字 (位置) を並べ替え、比較するときだけ keys を参照する。
*/

// chain[0, end) は keys の値で昇順に並んでいる。target をその範囲に挿入する位置を
// 二分探索で求める。等しい値があればその後ろを返す (std::upper_bound と同じ)
std::size_t	PmergeMe::_insertPositionVector(std::vector<std::size_t> const &chain,
	std::size_t end, std::size_t target, std::vector<unsigned int> const &keys)
{
	std::size_t	low = 0;
	std::size_t	high = end;

	while (low < high)
	{
		std::size_t const	mid = low + (high - low) / 2;

		if (keys[target] < keys[chain[mid]])
			high = mid;
		else
			low = mid + 1;
	}
	return (low);
}

std::size_t	PmergeMe::_insertPositionDeque(std::deque<std::size_t> const &chain,
	std::size_t end, std::size_t target, std::deque<unsigned int> const &keys)
{
	std::size_t	low = 0;
	std::size_t	high = end;

	while (low < high)
	{
		std::size_t const	mid = low + (high - low) / 2;

		if (keys[target] < keys[chain[mid]])
			high = mid;
		else
			low = mid + 1;
	}
	return (low);
}

std::vector<std::size_t>	PmergeMe::_fordJohnsonVector(std::vector<unsigned int> const &keys)
{
	std::size_t const	n = keys.size();
	std::size_t const	pairCount = n / 2;

	if (n < 2)
		return (std::vector<std::size_t>(n, 0));

	// 1. 組を作り、大きい方 (winner) と小さい方 (loser) の添字を記録する
	std::vector<std::size_t>	winners(pairCount);
	std::vector<std::size_t>	losers(pairCount);
	std::vector<unsigned int>	winnerKeys(pairCount);

	for (std::size_t i = 0; i < pairCount; ++i)
	{
		std::size_t	big = 2 * i;
		std::size_t	small = 2 * i + 1;

		if (keys[big] < keys[small])
			std::swap(big, small);
		winners[i] = big;
		losers[i] = small;
		winnerKeys[i] = keys[big];
	}

	// 2. winner だけを再帰的にソートする。戻り値は winners 内の位置の並び
	std::vector<std::size_t> const	sortedPairs = _fordJohnsonVector(winnerKeys);

	std::vector<std::size_t>	chain;
	std::vector<std::size_t>	pend;

	chain.reserve(n);
	pend.reserve(pairCount + 1);
	for (std::size_t i = 0; i < pairCount; ++i)
	{
		chain.push_back(winners[sortedPairs[i]]);
		pend.push_back(losers[sortedPairs[i]]);
	}
	if (n % 2 == 1)
		pend.push_back(n - 1);

	// 3. b1 は a1 以下なので先頭に置くだけでよい
	chain.insert(chain.begin(), pend[0]);

	// 4. ヤコブスタール数 1, 3, 5, 11, 21, ... で区切って、各グループを後ろから挿入する
	std::size_t	prevJacobsthal = 1;
	std::size_t	currJacobsthal = 3;

	while (prevJacobsthal < pend.size())
	{
		std::size_t const	groupEnd = std::min(currJacobsthal, pend.size());

		// k は 1 始まりの番号 (bk)。pend[k - 1] が bk にあたる
		for (std::size_t k = groupEnd; k > prevJacobsthal; --k)
		{
			std::size_t const	target = pend[k - 1];
			std::size_t			bound = chain.size();

			// 相方 ak がいるなら、探索範囲は ak の手前まで。
			// ak の現在位置は添字の一致で探すので、値の比較回数には含まれない
			if (k - 1 < pairCount)
				bound = std::find(chain.begin(), chain.end(), winners[sortedPairs[k - 1]])
					- chain.begin();
			chain.insert(chain.begin() + _insertPositionVector(chain, bound, target, keys),
				target);
		}
		std::size_t const	nextJacobsthal = currJacobsthal + 2 * prevJacobsthal;
		prevJacobsthal = currJacobsthal;
		currJacobsthal = nextJacobsthal;
	}
	return (chain);
}

std::deque<std::size_t>	PmergeMe::_fordJohnsonDeque(std::deque<unsigned int> const &keys)
{
	std::size_t const	n = keys.size();
	std::size_t const	pairCount = n / 2;

	if (n < 2)
		return (std::deque<std::size_t>(n, 0));

	// 1. 組を作り、大きい方 (winner) と小さい方 (loser) の添字を記録する
	std::deque<std::size_t>		winners(pairCount);
	std::deque<std::size_t>		losers(pairCount);
	std::deque<unsigned int>	winnerKeys(pairCount);

	for (std::size_t i = 0; i < pairCount; ++i)
	{
		std::size_t	big = 2 * i;
		std::size_t	small = 2 * i + 1;

		if (keys[big] < keys[small])
			std::swap(big, small);
		winners[i] = big;
		losers[i] = small;
		winnerKeys[i] = keys[big];
	}

	// 2. winner だけを再帰的にソートする。戻り値は winners 内の位置の並び
	std::deque<std::size_t> const	sortedPairs = _fordJohnsonDeque(winnerKeys);

	std::deque<std::size_t>	chain;
	std::deque<std::size_t>	pend;

	for (std::size_t i = 0; i < pairCount; ++i)
	{
		chain.push_back(winners[sortedPairs[i]]);
		pend.push_back(losers[sortedPairs[i]]);
	}
	if (n % 2 == 1)
		pend.push_back(n - 1);

	// 3. b1 は a1 以下なので先頭に置くだけでよい (deque は先頭への追加が O(1))
	chain.push_front(pend[0]);

	// 4. ヤコブスタール数 1, 3, 5, 11, 21, ... で区切って、各グループを後ろから挿入する
	std::size_t	prevJacobsthal = 1;
	std::size_t	currJacobsthal = 3;

	while (prevJacobsthal < pend.size())
	{
		std::size_t const	groupEnd = std::min(currJacobsthal, pend.size());

		// k は 1 始まりの番号 (bk)。pend[k - 1] が bk にあたる
		for (std::size_t k = groupEnd; k > prevJacobsthal; --k)
		{
			std::size_t const	target = pend[k - 1];
			std::size_t			bound = chain.size();

			// 相方 ak がいるなら、探索範囲は ak の手前まで。
			// ak の現在位置は添字の一致で探すので、値の比較回数には含まれない
			if (k - 1 < pairCount)
				bound = std::find(chain.begin(), chain.end(), winners[sortedPairs[k - 1]])
					- chain.begin();
			chain.insert(chain.begin() + _insertPositionDeque(chain, bound, target, keys),
				target);
		}
		std::size_t const	nextJacobsthal = currJacobsthal + 2 * prevJacobsthal;
		prevJacobsthal = currJacobsthal;
		currJacobsthal = nextJacobsthal;
	}
	return (chain);
}

void	PmergeMe::sortVector(void)
{
	std::vector<std::size_t> const	order = _fordJohnsonVector(this->_vector);
	std::vector<unsigned int>		sorted;

	sorted.reserve(order.size());
	for (std::size_t i = 0; i < order.size(); ++i)
		sorted.push_back(this->_vector[order[i]]);
	this->_vector.swap(sorted);
}

void	PmergeMe::sortDeque(void)
{
	std::deque<std::size_t> const	order = _fordJohnsonDeque(this->_deque);
	std::deque<unsigned int>		sorted;

	for (std::size_t i = 0; i < order.size(); ++i)
		sorted.push_back(this->_deque[order[i]]);
	this->_deque.swap(sorted);
}
