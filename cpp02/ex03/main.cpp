#include "Point.hpp"
#include <iostream>
#include <string>

// 1 つの点について bsp を実行し、期待する判定と並べて表示する。
// 結果がずれていれば一目で分かるようにするため。
static void	test(Point const &a, Point const &b, Point const &c,
		Point const &point, std::string const &expected)
{
	std::string const	got = bsp(a, b, c, point) ? "内側" : "外側";

	std::cout << "(" << point.getX() << ", " << point.getY() << ")"
		<< "\t結果: " << got << "\t期待: " << expected << std::endl;
}

int	main(void)
{
	Point const	a(0.0f, 0.0f);
	Point const	b(10.0f, 0.0f);
	Point const	c(0.0f, 10.0f);

	std::cout << "=== 三角形 (0,0) (10,0) (0,10) ===" << std::endl;
	test(a, b, c, Point(1.0f, 1.0f), "内側");
	test(a, b, c, Point(4.5f, 4.5f), "内側");
	test(a, b, c, Point(0.01f, 0.01f), "内側");
	test(a, b, c, Point(0.0f, 0.0f), "外側 (頂点の上)");
	test(a, b, c, Point(10.0f, 0.0f), "外側 (頂点の上)");
	test(a, b, c, Point(5.0f, 0.0f), "外側 (辺の上)");
	test(a, b, c, Point(5.0f, 5.0f), "外側 (斜辺の上)");
	test(a, b, c, Point(-1.0f, 5.0f), "外側");
	test(a, b, c, Point(6.0f, 6.0f), "外側");

	// 同じ三角形を、頂点の順序だけ逆向きにして渡す
	std::cout << "=== 同じ三角形・頂点の順序を逆にした場合 ===" << std::endl;
	test(c, b, a, Point(1.0f, 1.0f), "内側");
	test(c, b, a, Point(6.0f, 6.0f), "外側");

	std::cout << "=== 潰れた三角形 (一直線) ===" << std::endl;
	Point const	d(0.0f, 0.0f);
	Point const	e(5.0f, 0.0f);
	Point const	f(10.0f, 0.0f);

	test(d, e, f, Point(2.0f, 0.0f), "外側 (面積が 0)");

	std::cout << "=== 負の座標 ===" << std::endl;
	Point const	g(-5.0f, -5.0f);
	Point const	h(5.0f, -5.0f);
	Point const	i(0.0f, 5.0f);

	test(g, h, i, Point(0.0f, 0.0f), "内側");
	test(g, h, i, Point(-4.0f, 4.0f), "外側");

	return (0);
}
