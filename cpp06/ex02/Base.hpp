#ifndef BASE_HPP
# define BASE_HPP

// public な仮想デストラクタだけを持つ基底クラス。
// 仮想関数を 1 つでも持つ (多相型である) ことで dynamic_cast が使えるようになる。
class Base
{
	public:
		virtual ~Base(void);
};

#endif
