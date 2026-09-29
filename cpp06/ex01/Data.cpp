#include "Data.hpp"

// -------------------------------- 正準形 ----------------------------------

Data::Data(void) : id(0), name(""), value(0.0)
{
}

Data::Data(Data const &src) : id(src.id), name(src.name), value(src.value)
{
}

Data &Data::operator=(Data const &rhs)
{
	if (this != &rhs)
	{
		this->id = rhs.id;
		this->name = rhs.name;
		this->value = rhs.value;
	}
	return (*this);
}

Data::~Data(void)
{
}
