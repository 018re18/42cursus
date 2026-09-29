#include <iostream>
#include <string>

#include "whatever.hpp"

// 比較演算子を一通り持つ自作クラス。
// 値 (n) が同じでも id で区別できるので、等しいときにどちらが返ったかを確認できる。
class Awesome
{
	public:
		Awesome(void) : _n(0), _id('?') {}
		Awesome(int n, char id) : _n(n), _id(id) {}
		Awesome(Awesome const &src) : _n(src._n), _id(src._id) {}
		Awesome	&operator=(Awesome const &rhs)
		{
			_n = rhs._n;
			_id = rhs._id;
			return (*this);
		}
		~Awesome(void) {}

		bool	operator==(Awesome const &rhs) const { return (_n == rhs._n); }
		bool	operator!=(Awesome const &rhs) const { return (_n != rhs._n); }
		bool	operator<(Awesome const &rhs) const { return (_n < rhs._n); }
		bool	operator>(Awesome const &rhs) const { return (_n > rhs._n); }
		bool	operator<=(Awesome const &rhs) const { return (_n <= rhs._n); }
		bool	operator>=(Awesome const &rhs) const { return (_n >= rhs._n); }
		int		getN(void) const { return (_n); }
		char	getId(void) const { return (_id); }

	private:
		int		_n;
		char	_id;
};

std::ostream	&operator<<(std::ostream &o, Awesome const &a)
{
	o << a.getN() << "(" << a.getId() << ")";
	return (o);
}

// 課題 PDF に載っている main そのまま
static void	subjectTest(void)
{
	int	a = 2;
	int	b = 3;

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

	std::string	c = "chaine1";
	std::string	d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
}

// 等しいときは 2 つ目が返ることを、アドレスと id で確認する
static void	equalTest(void)
{
	std::cout << "=== equal values -> second one ===" << std::endl;
	int	x = 42;
	int	y = 42;

	std::cout << "&min(x, y) == &y : " << (&::min(x, y) == &y ? "OK" : "NG") << std::endl;
	std::cout << "&max(x, y) == &y : " << (&::max(x, y) == &y ? "OK" : "NG") << std::endl;

	Awesome	p(1, 'p');
	Awesome	q(1, 'q');

	std::cout << "min(p, q) = " << ::min(p, q) << ", max(p, q) = " << ::max(p, q) << std::endl;
}

static void	otherTypesTest(void)
{
	std::cout << "=== other types ===" << std::endl;
	Awesome	a(2, 'a');
	Awesome	b(4, 'b');

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << ", max(a, b) = " << ::max(a, b) << std::endl;

	double	d1 = -0.5;
	double	d2 = 1.25;

	std::cout << "min(-0.5, 1.25) = " << ::min(d1, d2) << ", max = " << ::max(d1, d2) << std::endl;

	char	c1 = 'z';
	char	c2 = 'a';

	::swap(c1, c2);
	std::cout << "c1 = " << c1 << ", c2 = " << c2 << std::endl;

	// const な値やリテラルも渡せる
	int const	k1 = 10;
	int const	k2 = -10;

	std::cout << "min(10, -10) = " << ::min(k1, k2) << ", max(3, 7) = " << ::max(3, 7) << std::endl;

	// 自分自身との swap でも壊れない
	std::string	s = "self";

	::swap(s, s);
	std::cout << "swap(s, s) -> " << s << std::endl;

	// ::swap(k1, k2);     // const なのでコンパイルエラー
	// ::min(1, 2.0);      // 型が違うのでコンパイルエラー
}

int	main(void)
{
	subjectTest();
	equalTest();
	otherTypesTest();
	return (0);
}
