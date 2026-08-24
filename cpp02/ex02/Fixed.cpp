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

Fixed	Fixed::_fromRaw(int const raw)
{
	Fixed	result;

	result.setRawBits(raw);
	return (result);
}

// --------------------------------- 比較 -----------------------------------

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

// ------------------------------- 四則演算 ---------------------------------

// 両辺が同じスケールを持つので、加算と減算ではスケールがそのまま残る。
Fixed	Fixed::operator+(Fixed const &rhs) const
{
	return (Fixed::_fromRaw(this->_value + rhs._value));
}

Fixed	Fixed::operator-(Fixed const &rhs) const
{
	return (Fixed::_fromRaw(this->_value - rhs._value));
}

// 生の値どうしを掛けるとスケールが 2 乗になるので、1 回分を割って戻す。
// 途中で int があふれないよう long で計算し、
// _fractionalBits ビットの右シフトがその _scale による除算にあたる。
Fixed	Fixed::operator*(Fixed const &rhs) const
{
	long const	raw = static_cast<long>(this->_value) * rhs._value;

	return (Fixed::_fromRaw(static_cast<int>(raw >> Fixed::_fractionalBits)));
}

// 生の値どうしを割るとスケールが完全に消えるので、あらかじめ掛けておく。
Fixed	Fixed::operator/(Fixed const &rhs) const
{
	long const	raw = static_cast<long>(this->_value) * Fixed::_scale
		/ rhs._value;

	return (Fixed::_fromRaw(static_cast<int>(raw)));
}

// ------------------- インクリメント / デクリメント -------------------------

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

// ------------------------------- min / max --------------------------------

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

// ------------------------------ 出力演算子 --------------------------------

std::ostream &operator<<(std::ostream &os, Fixed const &fixed)
{
	os << fixed.toFloat();
	return (os);
}
