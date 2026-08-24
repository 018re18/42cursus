#include "Point.hpp"

Point::Point(void) : _x(0), _y(0)
{
}

Point::Point(float const x, float const y) : _x(x), _y(y)
{
}

Point::Point(Point const &src) : _x(src._x), _y(src._y)
{
}

// _x と _y は const なので代入し直すことができない。したがって、この
// インスタンスを何も変えずに返すことだけが妥当な振る舞いになる。
// それでも直交正準形を守るために定義だけは用意しておく。
Point &Point::operator=(Point const &rhs)
{
	(void)rhs;
	return (*this);
}

Point::~Point(void)
{
}

Fixed const	&Point::getX(void) const
{
	return (this->_x);
}

Fixed const	&Point::getY(void) const
{
	return (this->_y);
}
