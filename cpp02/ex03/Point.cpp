#include "Point.hpp"

Point::Point(void) : _x(0), _y(0)
{
	return ;
}

Point::Point(float const x, float const y) : _x(x), _y(y)
{
	return ;
}

Point::Point(Point const &src) : _x(src._x), _y(src._y)
{
	return ;
}

/*
** _x and _y are const, so they can never be reassigned: the only sane
** behaviour left for the copy assignment operator is to keep this instance
** untouched. It is still provided to respect the Orthodox Canonical Form.
*/
Point &Point::operator=(Point const &rhs)
{
	(void)rhs;
	return (*this);
}

Point::~Point(void)
{
	return ;
}

Fixed const	&Point::getX(void) const
{
	return (this->_x);
}

Fixed const	&Point::getY(void) const
{
	return (this->_y);
}
