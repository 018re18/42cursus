#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed(void) : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(int const value)
{
	std::cout << "Int constructor called" << std::endl;
	this->_value = value << Fixed::_fractionalBits;
}

Fixed::Fixed(float const value)
{
	std::cout << "Float constructor called" << std::endl;
	this->_value = static_cast<int>(roundf(value * (1 << Fixed::_fractionalBits)));
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

int	Fixed::getRawBits(void) const
{
	return (this->_value);
}

void	Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(this->_value) / (1 << Fixed::_fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (this->_value >> Fixed::_fractionalBits);
}

/* ------------------------------ comparison ------------------------------ */

bool	Fixed::operator>(Fixed const &rhs) const
{
	return (this->_value > rhs._value);
}

bool	Fixed::operator<(Fixed const &rhs) const
{
	return (this->_value < rhs._value);
}

bool	Fixed::operator>=(Fixed const &rhs) const
{
	return (this->_value >= rhs._value);
}

bool	Fixed::operator<=(Fixed const &rhs) const
{
	return (this->_value <= rhs._value);
}

bool	Fixed::operator==(Fixed const &rhs) const
{
	return (this->_value == rhs._value);
}

bool	Fixed::operator!=(Fixed const &rhs) const
{
	return (this->_value != rhs._value);
}

/* ------------------------------ arithmetic ------------------------------ */

Fixed	Fixed::operator+(Fixed const &rhs) const
{
	Fixed	result;

	result.setRawBits(this->_value + rhs._value);
	return (result);
}

Fixed	Fixed::operator-(Fixed const &rhs) const
{
	Fixed	result;

	result.setRawBits(this->_value - rhs._value);
	return (result);
}

Fixed	Fixed::operator*(Fixed const &rhs) const
{
	Fixed	result;
	long	raw;

	raw = static_cast<long>(this->_value) * rhs._value;
	result.setRawBits(static_cast<int>(raw >> Fixed::_fractionalBits));
	return (result);
}

Fixed	Fixed::operator/(Fixed const &rhs) const
{
	Fixed	result;
	long	raw;

	raw = (static_cast<long>(this->_value) << Fixed::_fractionalBits) / rhs._value;
	result.setRawBits(static_cast<int>(raw));
	return (result);
}

/* ------------------------- increment / decrement ------------------------ */

Fixed	&Fixed::operator++(void)
{
	this->_value++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	old(*this);

	this->_value++;
	return (old);
}

Fixed	&Fixed::operator--(void)
{
	this->_value--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	old(*this);

	this->_value--;
	return (old);
}

/* -------------------------------- min/max ------------------------------- */

Fixed	&Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b ? a : b);
}

Fixed const	&Fixed::min(Fixed const &a, Fixed const &b)
{
	return (a < b ? a : b);
}

Fixed	&Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b ? a : b);
}

Fixed const	&Fixed::max(Fixed const &a, Fixed const &b)
{
	return (a > b ? a : b);
}

/* ------------------------------- insertion ------------------------------ */

std::ostream &operator<<(std::ostream &os, Fixed const &fixed)
{
	os << fixed.toFloat();
	return (os);
}
