#include "Point.hpp"

// 外積 (b - a) x (p - a) の z 成分。
// その符号が、向きを持つ直線 (a -> b) のどちら側に点 p があるかを示す。
// 正なら左側、負なら右側、0 なら直線上。
static Fixed	cross(Point const &a, Point const &b, Point const &p)
{
	return ((b.getX() - a.getX()) * (p.getY() - a.getY())
		- (b.getY() - a.getY()) * (p.getX() - a.getX()));
}

// 3 辺すべてに対して同じ側にあるとき、点は三角形の内側にある。
// a, b, c を与える順序 (時計回り / 反時計回り) がどちらでも成り立つ。
bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed const	zero(0);
	Fixed const	d1 = cross(a, b, point);
	Fixed const	d2 = cross(b, c, point);
	Fixed const	d3 = cross(c, a, point);
	bool		hasNeg;
	bool		hasPos;

	// 0 が出た場合は、辺の上・頂点の上・三角形が潰れているのいずれか
	if (d1 == zero || d2 == zero || d3 == zero)
		return (false);
	hasNeg = (d1 < zero) || (d2 < zero) || (d3 < zero);
	hasPos = (d1 > zero) || (d2 > zero) || (d3 > zero);
	return (!(hasNeg && hasPos));
}
