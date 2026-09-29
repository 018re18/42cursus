#ifndef RPN_HPP
# define RPN_HPP

#include <list>
#include <stack>
#include <string>

// 逆ポーランド記法 (Reverse Polish Notation) の式を評価する。
// 数値トークンは 1 桁 (0〜9)、演算子は + - * / のみを受け付ける。
class RPN
{
	private:
		// std::stack の既定の内部コンテナは std::deque だが、
		// deque は ex02 で使うため、ここでは std::list を内部コンテナに指定する
		std::stack<long, std::list<long> >	_stack;

		void	_applyOperator(char op);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		RPN(void);
		RPN(RPN const &src);
		RPN &operator=(RPN const &rhs);
		~RPN(void);

		// 式を評価して結果を返す。不正な式・ゼロ除算・オーバーフローでは例外を投げる
		long	evaluate(std::string const &expression);
};

#endif
