#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

// int 1 個に詰め込んだ固定小数点数。
// 下位 _fractionalBits ビットが小数部なので、_value が持つ生の値は常に
// (実際の値 * _scale) になる。
//   生の値 256 -> 1.0 / 生の値 128 -> 0.5
class Fixed
{
	private:
		static const int	_fractionalBits = 8;
		static const int	_scale = 1 << _fractionalBits;

		int					_value;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Fixed(void);
		Fixed(Fixed const &src);
		Fixed &operator=(Fixed const &rhs);
		~Fixed(void);

		// 変換
		Fixed(int const value);
		Fixed(float const value);
		float	toFloat(void) const;
		int		toInt(void) const;

		// 生の値へのアクセス
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
};

std::ostream &operator<<(std::ostream &os, Fixed const &fixed);

#endif
