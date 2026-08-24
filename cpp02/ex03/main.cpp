#include "Point.hpp"
#include <iostream>
#include <string>

static void	test(Point const &a, Point const &b, Point const &c,
		Point const &point, std::string const &label)
{
	bool const	result = bsp(a, b, c, point);

	std::cout << label << " -> " << (result ? "inside" : "outside")
		<< std::endl;
}

int	main(void)
{
	Point const	a(0.0f, 0.0f);
	Point const	b(10.0f, 0.0f);
	Point const	c(0.0f, 10.0f);

	std::cout << "=== triangle (0,0) (10,0) (0,10) ===" << std::endl;
	test(a, b, c, Point(1.0f, 1.0f), "(1, 1)      inside      ");
	test(a, b, c, Point(4.5f, 4.5f), "(4.5, 4.5)  inside      ");
	test(a, b, c, Point(0.0f, 0.0f), "(0, 0)      vertex      ");
	test(a, b, c, Point(10.0f, 0.0f), "(10, 0)     vertex      ");
	test(a, b, c, Point(5.0f, 0.0f), "(5, 0)      on edge     ");
	test(a, b, c, Point(5.0f, 5.0f), "(5, 5)      on hypotenuse");
	test(a, b, c, Point(-1.0f, 5.0f), "(-1, 5)     outside     ");
	test(a, b, c, Point(6.0f, 6.0f), "(6, 6)      outside     ");
	test(a, b, c, Point(0.01f, 0.01f), "(0.01,0.01) inside      ");

	// same triangle, vertices given in the opposite winding order
	std::cout << "=== same triangle, reversed winding ===" << std::endl;
	test(c, b, a, Point(1.0f, 1.0f), "(1, 1)      inside      ");
	test(c, b, a, Point(6.0f, 6.0f), "(6, 6)      outside     ");

	std::cout << "=== degenerate triangle (flat) ===" << std::endl;
	Point const	d(0.0f, 0.0f);
	Point const	e(5.0f, 0.0f);
	Point const	f(10.0f, 0.0f);
	test(d, e, f, Point(2.0f, 0.0f), "(2, 0)      degenerate  ");

	std::cout << "=== negative coordinates ===" << std::endl;
	Point const	g(-5.0f, -5.0f);
	Point const	h(5.0f, -5.0f);
	Point const	i(0.0f, 5.0f);
	test(g, h, i, Point(0.0f, 0.0f), "(0, 0)      inside      ");
	test(g, h, i, Point(-4.0f, 4.0f), "(-4, 4)     outside     ");

	return (0);
}
