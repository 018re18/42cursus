#ifndef FIXED_HPP
# define FIXED_HPP

// int 1 個に詰め込んだ固定小数点数。
// 下位 _fractionalBits ビットが小数部なので、_value が持つ生の値は常に
// (実際の値 * 2^_fractionalBits) になる。
//   生の値 256 -> 1.0 / 生の値 128 -> 0.5
class Fixed
{
	private:
		static const int	_fractionalBits = 8;

		int					_value;

	public:
		// 直交正準形 (Orthodox Canonical Form)
		Fixed(void);
		Fixed(Fixed const &src);
		Fixed &operator=(Fixed const &rhs);
		~Fixed(void);

		// 生の値へのアクセス
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
};

#endif
