#ifndef DATA_HPP
# define DATA_HPP

#include <string>

// シリアライズの対象。課題の指定どおり、データメンバを持つ (空でない) 構造体。
// struct もクラスの一種なので、直交正準形 (Orthodox Canonical Form) にしておく。
struct Data
{
	int			id;
	std::string	name;
	double		value;

	Data(void);
	Data(Data const &src);
	Data &operator=(Data const &rhs);
	~Data(void);
};

#endif
