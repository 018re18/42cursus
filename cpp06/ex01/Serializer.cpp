#include "Serializer.hpp"

// -------------------------------- 正準形 ----------------------------------
// インスタンス化させないために private にしているだけなので、中身は空。

Serializer::Serializer(void)
{
}

Serializer::Serializer(Serializer const &src)
{
	(void)src;
}

Serializer &Serializer::operator=(Serializer const &rhs)
{
	(void)rhs;
	return (*this);
}

Serializer::~Serializer(void)
{
}

// -------------------------------- 変換 ------------------------------------
// ポインタと整数のように、無関係な型どうしのビット表現をそのまま読み替えるのは
// reinterpret_cast の役目。static_cast ではコンパイルエラーになる。
// uintptr_t はポインタを保持できるだけの幅があることが保証されているので、
// ポインタ -> uintptr_t -> ポインタ と往復すれば元のポインタに戻る。

uintptr_t	Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data	*Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
