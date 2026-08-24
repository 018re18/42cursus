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

		// スケール済みの生の値から直接 Fixed を作る
		static Fixed		_fromRaw(int const raw);

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

		// 比較
		bool	operator>(Fixed const &rhs) const;
		bool	operator<(Fixed const &rhs) const;
		bool	operator>=(Fixed const &rhs) const;
		bool	operator<=(Fixed const &rhs) const;
		bool	operator==(Fixed const &rhs) const;
		bool	operator!=(Fixed const &rhs) const;

		// 四則演算
		Fixed	operator+(Fixed const &rhs) const;
		Fixed	operator-(Fixed const &rhs) const;
		Fixed	operator*(Fixed const &rhs) const;
		Fixed	operator/(Fixed const &rhs) const;

		// インクリメント / デクリメント。
		// 動く幅は生の値 1 つ分 (表現できる最小の値 = 1 / _scale)
		Fixed	&operator++(void);
		Fixed	operator++(int);
		Fixed	&operator--(void);
		Fixed	operator--(int);

		// min / max。書き換え可能版と読み取り専用版の 2 種類
		static Fixed		&min(Fixed &a, Fixed &b);
		static Fixed const	&min(Fixed const &a, Fixed const &b);
		static Fixed		&max(Fixed &a, Fixed &b);
		static Fixed const	&max(Fixed const &a, Fixed const &b);
};

std::ostream &operator<<(std::ostream &os, Fixed const &fixed);

#endif
