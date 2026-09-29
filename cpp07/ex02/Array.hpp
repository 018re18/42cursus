#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <cstddef>
#include <exception>

// 要素型 T の固定長配列。メモリは new[] で必要な分だけ確保する。
template <typename T>
class Array
{
	private:
		T				*_data;
		unsigned int	_size;

		static T		*duplicate(T const *src, unsigned int n);

	public:
		Array(void);
		// explicit を付けないと「a = 5;」が Array(5) への暗黙変換としてコンパイルでき、
		// 中身が要素数 5 の新しい配列に黙って置き換わってしまう
		explicit Array(unsigned int n);
		Array(Array const &src);
		Array &operator=(Array const &rhs);
		~Array(void);

		T				&operator[](std::size_t index);
		T const			&operator[](std::size_t index) const;
		unsigned int	size(void) const;

		// 範囲外アクセス時に投げる例外
		class OutOfBoundsException : public std::exception
		{
			public:
				OutOfBoundsException(void);
				OutOfBoundsException(OutOfBoundsException const &src);
				OutOfBoundsException &operator=(OutOfBoundsException const &rhs);
				virtual ~OutOfBoundsException(void) throw();

				virtual const char	*what(void) const throw();
		};
};

// テンプレートの定義はヘッダから見えている必要があるので、実装を .tpp に分けて末尾で読み込む
#include "Array.tpp"

#endif
