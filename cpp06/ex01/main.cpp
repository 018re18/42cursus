#include "Serializer.hpp"

#include <iostream>

static void	printData(Data const *data)
{
	std::cout << "  id    = " << data->id << std::endl;
	std::cout << "  name  = " << data->name << std::endl;
	std::cout << "  value = " << data->value << std::endl;
}

int	main(void)
{
	Data	data;

	data.id = 42;
	data.name = "Marvin";
	data.value = 3.14;

	Data		*original = &data;
	uintptr_t	raw = Serializer::serialize(original);
	Data		*restored = Serializer::deserialize(raw);

	std::cout << "original pointer : " << original << std::endl;
	std::cout << "serialized value : 0x" << std::hex << raw << std::dec << std::endl;
	std::cout << "restored pointer : " << restored << std::endl;

	if (restored == original)
		std::cout << "OK: deserialize(serialize(ptr)) == ptr" << std::endl;
	else
	{
		std::cout << "KO: pointers differ" << std::endl;
		return (1);
	}

	// 戻ってきたポインタ経由で、元のオブジェクトの中身が読めることも確かめる
	std::cout << "data via restored pointer:" << std::endl;
	printData(restored);
	return (0);
}
