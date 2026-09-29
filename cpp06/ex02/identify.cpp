#include "identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <iostream>

// 乱数の種 (srand) は main で一度だけ設定する
Base	*generate(void)
{
	switch (std::rand() % 3)
	{
		case 0:
			return (new A());
		case 1:
			return (new B());
		default:
			return (new C());
	}
}

// ポインタ版の dynamic_cast は、実際の型が違えば NULL を返す
void	identify(Base *p)
{
	if (dynamic_cast<A *>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

// 参照は NULL になれないので、参照版の dynamic_cast は失敗すると
// std::bad_cast を投げる。bad_cast は <typeinfo> で宣言されていて
// その include が禁止されているため、catch (...) で受ける。
// ポインタの使用も禁止なので、&p でポインタ版に委ねることもしない。
void	identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return ;
	}
	catch (...)
	{
	}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return ;
	}
	catch (...)
	{
	}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return ;
	}
	catch (...)
	{
	}
	std::cout << "Unknown type" << std::endl;
}
