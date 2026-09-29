#ifndef WHATEVER_HPP
# define WHATEVER_HPP

// テンプレートは使われた型ごとにコンパイル時に実体化されるので、
// 定義ごとヘッダに書いておく必要がある。

// 2 つの値を入れ替える。コピー代入ができる型なら何でもよい。
template <typename T>
void	swap(T &a, T &b)
{
	T	tmp = a;

	a = b;
	b = tmp;
}

// 小さい方を返す。等しいときは 2 つ目を返す (a < b のときだけ a)。
template <typename T>
T const	&min(T const &a, T const &b)
{
	return (a < b ? a : b);
}

// 大きい方を返す。等しいときは 2 つ目を返す (a > b のときだけ a)。
template <typename T>
T const	&max(T const &a, T const &b)
{
	return (a > b ? a : b);
}

#endif
