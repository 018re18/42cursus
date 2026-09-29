#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>

// C++ リテラルの文字列表現を受け取り、char / int / float / double の
// 4 つのスカラ型に変換して表示する。
// 何も保持しないクラスなので、コンストラクタ類をすべて private にして
// ユーザがインスタンス化できないようにしている。
class ScalarConverter
{
	private:
		ScalarConverter(void);
		ScalarConverter(ScalarConverter const &src);
		ScalarConverter &operator=(ScalarConverter const &rhs);
		~ScalarConverter(void);

	public:
		static void	convert(std::string const &literal);
};

#endif
