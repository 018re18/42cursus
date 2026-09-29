#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

// uintptr_t は C++11 の <cstdint> で入ったものなので、C++98 では C の <stdint.h> を使う
#include <stdint.h>

#include "Data.hpp"

// ポインタと整数 (uintptr_t) を相互に変換する。
// 状態を持たないので、コンストラクタ類をすべて private にして
// ユーザがインスタンス化できないようにしている。
class Serializer
{
	private:
		Serializer(void);
		Serializer(Serializer const &src);
		Serializer &operator=(Serializer const &rhs);
		~Serializer(void);

	public:
		static uintptr_t	serialize(Data *ptr);
		static Data			*deserialize(uintptr_t raw);
};

#endif
