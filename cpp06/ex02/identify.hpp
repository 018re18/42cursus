#ifndef IDENTIFY_HPP
# define IDENTIFY_HPP

#include "Base.hpp"

// A / B / C のいずれかをランダムに生成し、Base へのポインタとして返す
Base	*generate(void);

// 実際の型 ("A" / "B" / "C") を表示する。<typeinfo> (typeid) は使わない。
void	identify(Base *p);
void	identify(Base &p);

#endif
