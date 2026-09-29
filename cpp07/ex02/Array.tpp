#ifndef ARRAY_TPP
# define ARRAY_TPP

#include <cstddef>

#include "Array.hpp"

template <typename T>
Array<T>::Array(void) : _data(NULL), _size(0)
{
}

// new T[n]() の () で値初期化される。int なら 0、std::string なら空文字列になる。
// (() を付けないと int などの組み込み型は不定値のまま)
template <typename T>
Array<T>::Array(unsigned int n) : _data(NULL), _size(n)
{
	if (n > 0)
		_data = new T[n]();
}

// src の先頭 n 要素をコピーした新しい領域を返す (深いコピー)。
// T の代入が途中で例外を投げた場合は、確保した領域を解放してから例外を投げ直す。
// (これをしないと new[] した領域がどこからも指されずにリークする)
template <typename T>
T	*Array<T>::duplicate(T const *src, unsigned int n)
{
	if (n == 0)
		return (NULL);

	T	*dst = new T[n]();

	try
	{
		for (unsigned int i = 0; i < n; i++)
			dst[i] = src[i];
	}
	catch (...)
	{
		delete[] dst;
		throw ;
	}
	return (dst);
}

// ポインタをコピーするのではなく、新しい領域を確保して中身をコピーする (深いコピー)。
template <typename T>
Array<T>::Array(Array const &src) : _data(duplicate(src._data, src._size)), _size(src._size)
{
}

// 先に新しい領域を用意してから古い領域を解放する。
// こうしておくと new や T の代入が例外を投げても *this は元のまま残る。
template <typename T>
Array<T>	&Array<T>::operator=(Array const &rhs)
{
	if (this == &rhs)
		return (*this);

	T	*newData = duplicate(rhs._data, rhs._size);

	delete[] _data;
	_data = newData;
	_size = rhs._size;
	return (*this);
}

template <typename T>
Array<T>::~Array(void)
{
	delete[] _data;
}

// index は std::size_t なので、負の値を渡すと巨大な値になり、ここで範囲外として弾かれる。
// (unsigned int だと 2^32 以上の添字が切り詰められ、範囲内の別の要素を指してしまう)
template <typename T>
T	&Array<T>::operator[](std::size_t index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return (_data[index]);
}

// const な Array からは読み取りだけできるようにする
template <typename T>
T const	&Array<T>::operator[](std::size_t index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return (_data[index]);
}

template <typename T>
unsigned int	Array<T>::size(void) const
{
	return (_size);
}

template <typename T>
Array<T>::OutOfBoundsException::OutOfBoundsException(void) : std::exception()
{
}

template <typename T>
Array<T>::OutOfBoundsException::OutOfBoundsException(OutOfBoundsException const &src)
	: std::exception(src)
{
}

template <typename T>
typename Array<T>::OutOfBoundsException	&Array<T>::OutOfBoundsException::operator=(
	OutOfBoundsException const &rhs)
{
	std::exception::operator=(rhs);
	return (*this);
}

template <typename T>
Array<T>::OutOfBoundsException::~OutOfBoundsException(void) throw()
{
}

template <typename T>
const char	*Array<T>::OutOfBoundsException::what(void) const throw()
{
	return ("Array: index out of bounds");
}

#endif
