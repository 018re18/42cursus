#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <deque>
#include <stack>

// イテレータで走査できる std::stack。
// std::stack は中身を protected メンバ c (既定では std::deque) に持っているだけなので、
// 継承すれば c のイテレータをそのまま外に公開できる。
// push / pop / top / size / empty などは std::stack のものをそのまま受け継ぐ。
template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
	public:
		// 依存名なので typename が必要
		typedef typename Container::iterator				iterator;
		typedef typename Container::const_iterator			const_iterator;
		typedef typename Container::reverse_iterator		reverse_iterator;
		typedef typename Container::const_reverse_iterator	const_reverse_iterator;

		// 直交正準形 (Orthodox Canonical Form)
		MutantStack(void);
		MutantStack(MutantStack const &src);
		MutantStack &operator=(MutantStack const &rhs);
		~MutantStack(void);

		// begin は一番下 (最初に push した要素)、end - 1 は一番上 (top) を指す
		iterator				begin(void);
		iterator				end(void);
		const_iterator			begin(void) const;
		const_iterator			end(void) const;
		// 逆順は top から下へ向かって走査する
		reverse_iterator		rbegin(void);
		reverse_iterator		rend(void);
		const_reverse_iterator	rbegin(void) const;
		const_reverse_iterator	rend(void) const;
};

// テンプレートの定義はヘッダから見えている必要があるので、実装を .tpp に分けて末尾で読み込む
#include "MutantStack.tpp"

#endif
