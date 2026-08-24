#include "Point.hpp"

/*
** Z component of the cross product (b - a) x (p - a).
** Its sign tells on which side of the oriented line (a -> b) the point p lies.
*/
static Fixed	cross(Point const &a, Point const &b, Point const &p)
{
	return ((b.getX() - a.getX()) * (p.getY() - a.getY())
		- (b.getY() - a.getY()) * (p.getX() - a.getX()));
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed const	zero(0);
	Fixed const	d1 = cross(a, b, point);
	Fixed const	d2 = cross(b, c, point);
	Fixed const	d3 = cross(c, a, point);
	bool		hasNeg;
	bool		hasPos;

	// on an edge, on a vertex, or the triangle is degenerate
	if (d1 == zero || d2 == zero || d3 == zero)
		return (false);
	hasNeg = (d1 < zero) || (d2 < zero) || (d3 < zero);
	hasPos = (d1 > zero) || (d2 > zero) || (d3 > zero);
	return (!(hasNeg && hasPos));
}
