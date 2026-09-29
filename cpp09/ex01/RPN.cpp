#include "RPN.hpp"

#include <cctype>
#include <limits>
#include <sstream>
#include <stdexcept>

RPN::RPN(void)
{
}

RPN::RPN(RPN const &src)
	: _stack(src._stack)
{
}

RPN	&RPN::operator=(RPN const &rhs)
{
	if (this != &rhs)
		this->_stack = rhs._stack;
	return (*this);
}

RPN::~RPN(void)
{
}

long	RPN::evaluate(std::string const &expression)
{
	std::istringstream	iss(expression);
	std::string			token;

	while (!this->_stack.empty())
		this->_stack.pop();
	// トークンは空白区切り。1 文字でないトークン ("12", "(1" など) はすべてエラー
	while (iss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("invalid token: " + token);
		if (std::isdigit(static_cast<unsigned char>(token[0])))
			this->_stack.push(token[0] - '0');
		else
			this->_applyOperator(token[0]);
	}
	// 最後にちょうど 1 つの値が残っていなければ、オペランドが余っている (または空の式)
	if (this->_stack.size() != 1)
		throw std::runtime_error("invalid expression");
	return (this->_stack.top());
}

void	RPN::_applyOperator(char op)
{
	long const	max = std::numeric_limits<long>::max();
	long const	min = std::numeric_limits<long>::min();

	if (op != '+' && op != '-' && op != '*' && op != '/')
		throw std::runtime_error(std::string("invalid token: ") + op);
	if (this->_stack.size() < 2)
		throw std::runtime_error("not enough operands");

	// スタックの上にあるのが右オペランド。"5 3 -" は 5 - 3
	long const	b = this->_stack.top();
	this->_stack.pop();
	long const	a = this->_stack.top();
	this->_stack.pop();

	// 各演算の前に、結果が long に収まるかを確認する (符号付き整数のオーバーフローは未定義動作)
	switch (op)
	{
		case '+':
			if ((b > 0 && a > max - b) || (b < 0 && a < min - b))
				throw std::runtime_error("overflow");
			this->_stack.push(a + b);
			break ;
		case '-':
			if ((b < 0 && a > max + b) || (b > 0 && a < min + b))
				throw std::runtime_error("overflow");
			this->_stack.push(a - b);
			break ;
		case '*':
			if (a != 0 && b != 0
				&& ((a > 0 && b > 0 && a > max / b)
					|| (a > 0 && b < 0 && b < min / a)
					|| (a < 0 && b > 0 && a < min / b)
					|| (a < 0 && b < 0 && a < max / b)))
				throw std::runtime_error("overflow");
			this->_stack.push(a * b);
			break ;
		case '/':
			if (b == 0)
				throw std::runtime_error("division by zero");
			if (a == min && b == -1)
				throw std::runtime_error("overflow");
			this->_stack.push(a / b);
			break ;
	}
}
