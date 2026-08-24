#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

// 変更不可能な 2 次元の点。座標が両方とも const なので、生成とコピーはできるが
// 生成後に書き換えることはできない。
class Point
{
	private:
		Fixed const	_x;
		Fixed const	_y;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Point(void);
		Point(Point const &src);
		Point &operator=(Point const &rhs);
		~Point(void);

		Point(float const x, float const y);

		Fixed const	&getX(void) const;
		Fixed const	&getY(void) const;
};

// point が三角形 a-b-c の内側に厳密に入っていれば true。
// 辺の上と頂点の上は外側として扱う。
bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif
