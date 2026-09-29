#ifndef SPAN_HPP
# define SPAN_HPP

#include <exception>
#include <vector>

// 最大 N 個の int を保持し、要素間の最短・最長の差 (span) を求めるクラス。
class Span
{
	private:
		unsigned int		_maxSize;
		std::vector<int>	_numbers;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Span(void);
		Span(unsigned int n);
		Span(Span const &src);
		Span &operator=(Span const &rhs);
		~Span(void);

		void			addNumber(int number);
		// [first, last) の範囲をまとめて追加する。入り切らない場合は 1 つも追加せずに例外を投げる。
		// どんなイテレータ型でも受け取れるよう、メンバ関数テンプレートにしている。
		template <typename InputIt>
		void			addRange(InputIt first, InputIt last);

		// 差は最大で INT_MAX - INT_MIN = 4294967295 になり int に収まらないので unsigned int で返す
		unsigned int	shortestSpan(void) const;
		unsigned int	longestSpan(void) const;

		unsigned int	size(void) const;
		unsigned int	maxSize(void) const;

		// 満杯のときに追加しようとした
		class FullException : public std::exception
		{
			public:
				virtual const char	*what(void) const throw();
		};

		// 要素が 0 個か 1 個で span を求められない
		class NoSpanException : public std::exception
		{
			public:
				virtual const char	*what(void) const throw();
		};
};

// テンプレートなのでヘッダ内に定義を書く
template <typename InputIt>
void	Span::addRange(InputIt first, InputIt last)
{
	std::vector<int>		tmp;
	std::vector<int>::size_type	room = _maxSize - _numbers.size();

	// 一度 tmp に取り出してから追加することで、途中で失敗しても _numbers は変わらない。
	// 空きを超えた時点で打ち切るので、巨大な範囲を渡されても全部コピーすることはない。
	for (; first != last; ++first)
	{
		if (tmp.size() >= room)
			throw FullException();
		tmp.push_back(*first);
	}
	_numbers.insert(_numbers.end(), tmp.begin(), tmp.end());
}

#endif
