#include "Fixed.hpp"
#include <cmath>

// -------------------------------- 正準形 ----------------------------------

Fixed::Fixed(void) : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed &Fixed::operator=(Fixed const &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_value = rhs.getRawBits();
	return (*this);
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

// --------------------------------- 変換 -----------------------------------

// _fractionalBits ビット左シフトすることは _scale 倍することと同じ。
Fixed::Fixed(int const value) : _value(value << Fixed::_fractionalBits)
{
	std::cout << "Int constructor called" << std::endl;
}

// roundf を使うことで、切り捨てではなく最も近い表現可能な値に丸める。
Fixed::Fixed(float const value)
	: _value(static_cast<int>(roundf(value * Fixed::_scale)))
{
	std::cout << "Float constructor called" << std::endl;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(this->_value) / Fixed::_scale);
}

int	Fixed::toInt(void) const
{
	return (this->_value >> Fixed::_fractionalBits);
}

// ------------------------- 生の値へのアクセス ------------------------------

int	Fixed::getRawBits(void) const
{
	return (this->_value);
}

void	Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

// ------------------------------ 出力演算子 --------------------------------

std::ostream &operator<<(std::ostream &os, Fixed const &fixed)
{
	os << fixed.toFloat();
	return (os);
}
