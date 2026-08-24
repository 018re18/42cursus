#include "Fixed.hpp"
#include <iostream>

int	main(void)
{
	// ---------------------------- 課題のテスト ----------------------------
	Fixed		a;
	Fixed const	b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;

	// ---------------------------- 比較演算子 ------------------------------
	std::cout << "--- 比較 ---" << std::endl;
	Fixed const	x(10);
	Fixed const	y(10.5f);

	std::cout << "x < y   : " << (x < y) << std::endl;
	std::cout << "x > y   : " << (x > y) << std::endl;
	std::cout << "x <= x  : " << (x <= x) << std::endl;
	std::cout << "x >= y  : " << (x >= y) << std::endl;
	std::cout << "x == x  : " << (x == x) << std::endl;
	std::cout << "x != y  : " << (x != y) << std::endl;

	// ------------------------------ 四則演算 ------------------------------
	std::cout << "--- 四則演算 ---" << std::endl;
	std::cout << "x + y = " << (x + y) << std::endl;
	std::cout << "x - y = " << (x - y) << std::endl;
	std::cout << "x * y = " << (x * y) << std::endl;
	std::cout << "x / y = " << (x / y) << std::endl;

	// ------------------- 前置 / 後置デクリメント --------------------------
	std::cout << "--- デクリメント ---" << std::endl;
	Fixed	z;

	std::cout << z-- << std::endl;
	std::cout << z << std::endl;
	std::cout << --z << std::endl;

	// ------------------------------ min / max -----------------------------
	std::cout << "--- min / max ---" << std::endl;
	std::cout << Fixed::min(x, y) << std::endl;
	Fixed	m(3);
	Fixed	n(4);

	std::cout << Fixed::min(m, n) << " / " << Fixed::max(m, n) << std::endl;

	return (0);
}
