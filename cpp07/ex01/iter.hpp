#ifndef ITER_HPP
# define ITER_HPP

#include <cstddef>

// 配列の各要素に func を適用する。
//
// const 対応について:
//   T は配列の要素型から推論されるので、const int の配列を渡せば T = const int になる。
//   そのため const / 非 const の配列を 1 つのテンプレートで両方扱える。
//   func の型も F として丸ごと推論するので、
//     - void f(int &)          (要素を書き換える)
//     - void f(int const &)    (読むだけ)
//     - f<int> のように実体化した関数テンプレート
//     - operator() を持つ関数オブジェクト
//   のどれでも渡せる。
//   const の配列に「非 const 参照を取る関数」を渡した場合はコンパイルエラーになる (正しい挙動)。
template <typename T, typename F>
void	iter(T *array, size_t const length, F func)
{
	if (array == NULL)
		return ;
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

#endif
