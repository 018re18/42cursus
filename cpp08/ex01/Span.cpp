#include "Span.hpp"

#include <algorithm>

// low <= high である 2 つの int の差を返す。
// int 同士の high - low はオーバーフローし得る (例: INT_MAX - INT_MIN) ので、
// unsigned int に変換してから引く。unsigned の演算は 2^32 を法として行われるため、
// low <= high なら差 (最大 4294967295) が正しく求まる。
static unsigned int	gap(int low, int high)
{
	return (static_cast<unsigned int>(high) - static_cast<unsigned int>(low));
}

Span::Span(void) : _maxSize(0)
{
}

// ここで reserve(n) はしない。Span(4294967295) のような大きな N だと
// 使わない領域 (int 約 43 億個 = 16GB) まで確保しようとして std::bad_alloc になり得るため。
Span::Span(unsigned int n) : _maxSize(n)
{
}

Span::Span(Span const &src) : _maxSize(src._maxSize), _numbers(src._numbers)
{
}

Span	&Span::operator=(Span const &rhs)
{
	if (this != &rhs)
	{
		_maxSize = rhs._maxSize;
		_numbers = rhs._numbers;
	}
	return (*this);
}

Span::~Span(void)
{
}

void	Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw FullException();
	_numbers.push_back(number);
}

// ソートすると、最短の差は必ず隣り合う要素の間に現れる。O(n log n)
unsigned int	Span::shortestSpan(void) const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int>	sorted(_numbers);

	std::sort(sorted.begin(), sorted.end());
	unsigned int	shortest = gap(sorted[0], sorted[1]);
	for (std::vector<int>::size_type i = 2; i < sorted.size(); i++)
	{
		unsigned int	diff = gap(sorted[i - 1], sorted[i]);
		if (diff < shortest)
			shortest = diff;
	}
	return (shortest);
}

// 最長の差は 最大値 - 最小値。ソート不要で O(n)
unsigned int	Span::longestSpan(void) const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	int	min = *std::min_element(_numbers.begin(), _numbers.end());
	int	max = *std::max_element(_numbers.begin(), _numbers.end());
	return (gap(min, max));
}

unsigned int	Span::size(void) const
{
	return (_numbers.size());
}

unsigned int	Span::maxSize(void) const
{
	return (_maxSize);
}

const char	*Span::FullException::what(void) const throw()
{
	return ("Span: no room left to add numbers");
}

const char	*Span::NoSpanException::what(void) const throw()
{
	return ("Span: need at least two numbers to find a span");
}
