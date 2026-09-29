#ifndef EASYFIND_HPP
# define EASYFIND_HPP

// int を格納するコンテナ T から、value が最初に現れる位置のイテレータを返す。
// 見つからなければ std::runtime_error を投げる。
// (std::find は見つからないと end() を返すが、ここでは例外で知らせる方を選んだ。
//  独自の例外クラスを作ると what() の実装をヘッダに書くことになり課題のルールに反するので、
//  標準ライブラリの例外を使う)
template <typename T>
typename T::iterator		easyfind(T &container, int value);

// const なコンテナ用。const_iterator を返す。
template <typename T>
typename T::const_iterator	easyfind(T const &container, int value);

// テンプレートの定義はヘッダから見えている必要があるので、実装を .tpp に分けて末尾で読み込む
#include "easyfind.tpp"

#endif
