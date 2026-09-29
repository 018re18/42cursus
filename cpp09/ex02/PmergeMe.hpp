#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <cstddef>
#include <deque>
#include <string>
#include <vector>

// 正の整数列を Ford-Johnson アルゴリズム (merge-insertion sort) でソートする。
// 同じ処理を std::vector と std::deque のそれぞれで実装し、速度を比較する。
// 課題文の推奨に従い、テンプレートで共通化せずコンテナごとに別の関数として書いている。
class PmergeMe
{
	private:
		std::vector<unsigned int>	_vector;
		std::deque<unsigned int>	_deque;

		static unsigned int	_parseNumber(std::string const &token);

		// keys を昇順に並べたときの添字の並び (keys[order[0]] <= keys[order[1]] <= ...) を返す
		static std::vector<std::size_t>	_fordJohnsonVector(std::vector<unsigned int> const &keys);
		static std::deque<std::size_t>	_fordJohnsonDeque(std::deque<unsigned int> const &keys);

		// 昇順に並んだ chain[0, end) の中で、target を挿入すべき位置を二分探索で返す
		static std::size_t	_insertPositionVector(std::vector<std::size_t> const &chain,
			std::size_t end, std::size_t target, std::vector<unsigned int> const &keys);
		static std::size_t	_insertPositionDeque(std::deque<std::size_t> const &chain,
			std::size_t end, std::size_t target, std::deque<unsigned int> const &keys);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		PmergeMe(void);
		PmergeMe(PmergeMe const &src);
		PmergeMe &operator=(PmergeMe const &rhs);
		~PmergeMe(void);

		// コマンドライン引数を解析して各コンテナに格納する。不正な値があれば例外を投げる
		void	loadVector(int argc, char **argv);
		void	loadDeque(int argc, char **argv);

		void	sortVector(void);
		void	sortDeque(void);

		std::vector<unsigned int> const	&getVector(void) const;
		std::deque<unsigned int> const	&getDeque(void) const;
};

#endif
