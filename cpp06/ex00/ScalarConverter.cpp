#include "ScalarConverter.hpp"

#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

// -------------------------------- 正準形 ----------------------------------
// インスタンス化させないために private にしているだけなので、中身は空。

ScalarConverter::ScalarConverter(void)
{
}

ScalarConverter::ScalarConverter(ScalarConverter const &src)
{
	(void)src;
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &rhs)
{
	(void)rhs;
	return (*this);
}

ScalarConverter::~ScalarConverter(void)
{
}

// 以下の補助関数はこの翻訳単位の中だけで使うので、無名名前空間に閉じ込める。
namespace
{
	enum e_type
	{
		TYPE_INVALID,
		TYPE_CHAR,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE
	};

	double const	g_inf = std::numeric_limits<double>::infinity();
	double const	g_nan = std::numeric_limits<double>::quiet_NaN();

	// ---------------------------- 型の判定 --------------------------------

	bool	isPrintable(char c)
	{
		return (std::isprint(static_cast<unsigned char>(c)) != 0);
	}

	bool	isDigit(char c)
	{
		return (std::isdigit(static_cast<unsigned char>(c)) != 0);
	}

	// 先頭の符号 (+/-) を読み飛ばした位置を返す
	std::size_t	skipSign(std::string const &s)
	{
		if (!s.empty() && (s[0] == '+' || s[0] == '-'))
			return (1);
		return (0);
	}

	// 'a' のようにクォートで囲んだ形と、a のように 1 文字だけの形を受け付ける。
	// 1 文字の数字 (例: 0) は int として扱うので char からは除外する。
	bool	isCharLiteral(std::string const &s)
	{
		if (s.length() == 3 && s[0] == '\'' && s[2] == '\'')
			return (isPrintable(s[1]));
		return (s.length() == 1 && isPrintable(s[0]) && !isDigit(s[0]));
	}

	// [+-]? 数字+
	bool	isIntLiteral(std::string const &s)
	{
		std::size_t	i = skipSign(s);

		if (i == s.length())
			return (false);
		for (; i < s.length(); ++i)
		{
			if (!isDigit(s[i]))
				return (false);
		}
		return (true);
	}

	// [+-]? の後に小数点がちょうど 1 つ、数字が 1 つ以上ある形
	// (例: 4.2 / 42. / .5)。10 進表記のみなので指数表記は受け付けない。
	bool	isDecimalLiteral(std::string const &s)
	{
		std::size_t	i = skipSign(s);
		std::size_t	digits = 0;
		bool		dot = false;

		for (; i < s.length(); ++i)
		{
			if (isDigit(s[i]))
				++digits;
			else if (s[i] == '.' && !dot)
				dot = true;
			else
				return (false);
		}
		return (dot && digits > 0);
	}

	bool	isFloatPseudoLiteral(std::string const &s)
	{
		return (s == "-inff" || s == "+inff" || s == "inff" || s == "nanf");
	}

	bool	isDoublePseudoLiteral(std::string const &s)
	{
		return (s == "-inf" || s == "+inf" || s == "inf" || s == "nan");
	}

	// 10 進の小数表記 + 末尾の 'f'
	bool	isFloatLiteral(std::string const &s)
	{
		if (isFloatPseudoLiteral(s))
			return (true);
		if (s.length() < 2 || s[s.length() - 1] != 'f')
			return (false);
		return (isDecimalLiteral(s.substr(0, s.length() - 1)));
	}

	bool	isDoubleLiteral(std::string const &s)
	{
		return (isDoublePseudoLiteral(s) || isDecimalLiteral(s));
	}

	e_type	detectType(std::string const &s)
	{
		if (isCharLiteral(s))
			return (TYPE_CHAR);
		if (isIntLiteral(s))
			return (TYPE_INT);
		if (isFloatLiteral(s))
			return (TYPE_FLOAT);
		if (isDoubleLiteral(s))
			return (TYPE_DOUBLE);
		return (TYPE_INVALID);
	}

	// ---------------------------- 文字列からの変換 ------------------------
	// いずれもオーバーフローしたら false を返す。

	bool	parseInt(std::string const &s, int &out)
	{
		errno = 0;
		long const	value = std::strtol(s.c_str(), NULL, 10);

		if (errno == ERANGE || value < std::numeric_limits<int>::min()
			|| value > std::numeric_limits<int>::max())
			return (false);
		out = static_cast<int>(value);
		return (true);
	}

	// 疑似リテラル (inf / nan) は strtod に任せず自前で値を作る
	bool	parseDouble(std::string const &s, double &out)
	{
		if (s == "nan")
			out = g_nan;
		else if (s == "inf" || s == "+inf")
			out = g_inf;
		else if (s == "-inf")
			out = -g_inf;
		else
		{
			errno = 0;
			out = std::strtod(s.c_str(), NULL);
			// ERANGE はアンダーフロー (0 に丸め) でも立つので、
			// 結果が HUGE_VAL のときだけオーバーフローとみなす
			if (errno == ERANGE && std::fabs(out) == HUGE_VAL)
				return (false);
		}
		return (true);
	}

	// C++98 には strtof が無いので、末尾の 'f' を外して double として読み、
	// float の範囲に収まるか確かめてから float に変換する
	bool	parseFloat(std::string const &s, float &out)
	{
		double	value;

		if (!parseDouble(s.substr(0, s.length() - 1), value))
			return (false);
		if (value == value && value != g_inf && value != -g_inf
			&& std::fabs(value) > std::numeric_limits<float>::max())
			return (false);
		out = static_cast<float>(value);
		return (true);
	}

	// ---------------------------- 範囲の検査 ------------------------------
	// char / int / float の値はすべて double で正確に表せるので、double で受ける。
	// 範囲外の浮動小数点数を整数型にキャストするのは未定義動作なので、
	// キャストする前に必ずこれで検査する。
	// 浮動小数点数 -> 整数の変換は小数部を切り捨てるので、切り捨てた後に
	// 収まれば OK (例: 127.5 -> 127)。そのため (min - 1, max + 1) の開区間で判定する。
	// nan との比較は常に false になるため、nan も「範囲外」として弾かれる。

	bool	fitsChar(double value)
	{
		return (value > std::numeric_limits<char>::min() - 1.0
			&& value < std::numeric_limits<char>::max() + 1.0);
	}

	bool	fitsInt(double value)
	{
		return (value > std::numeric_limits<int>::min() - 1.0
			&& value < std::numeric_limits<int>::max() + 1.0);
	}

	// inf と nan は float でも表せるので「収まる」扱い
	bool	fitsFloat(double value)
	{
		if (value != value || value == g_inf || value == -g_inf)
			return (true);
		return (std::fabs(value) <= std::numeric_limits<float>::max());
	}

	// ---------------------------- 表示 ------------------------------------

	// 浮動小数点数を文字列にする。整数値のときは "42" ではなく "42.0" になるよう
	// 小数部を補う。precision は有効桁数で、表示する型の精度に合わせる。
	std::string	formatFloating(double value, int precision)
	{
		if (value != value)
			return ("nan");
		if (value == g_inf)
			return ("+inf");
		if (value == -g_inf)
			return ("-inf");

		std::ostringstream	oss;
		oss << std::setprecision(precision) << value;
		std::string	str = oss.str();
		if (str.find('.') == std::string::npos && str.find('e') == std::string::npos)
			str += ".0";
		return (str);
	}

	void	printImpossible(char const *typeName)
	{
		std::cout << typeName << ": impossible" << std::endl;
	}

	void	printChar(char c)
	{
		if (isPrintable(c))
			std::cout << "char: '" << c << "'" << std::endl;
		else
			std::cout << "char: Non displayable" << std::endl;
	}

	void	printInt(int i)
	{
		std::cout << "int: " << i << std::endl;
	}

	void	printFloat(float f)
	{
		std::cout << "float: "
			<< formatFloating(f, std::numeric_limits<float>::digits10)
			<< "f" << std::endl;
	}

	// 元の型が float のときは、double に広げても精度は float のままなので
	// float の桁数で表示する (4.2f が 4.19999980926514 と出ないように)
	void	printDouble(double d, int precision)
	{
		std::cout << "double: " << formatFloating(d, precision) << std::endl;
	}

	void	printAllImpossible(void)
	{
		printImpossible("char");
		printImpossible("int");
		printImpossible("float");
		printImpossible("double");
	}

	// ---------------------------- 型ごとの変換 ----------------------------
	// 実際の型の値から、残り 3 つの型へ static_cast で明示的に変換する。

	void	convertFromChar(char c)
	{
		printChar(c);
		printInt(static_cast<int>(c));
		printFloat(static_cast<float>(c));
		printDouble(static_cast<double>(c), std::numeric_limits<double>::digits10);
	}

	void	convertFromInt(int i)
	{
		if (fitsChar(i))
			printChar(static_cast<char>(i));
		else
			printImpossible("char");
		printInt(i);
		printFloat(static_cast<float>(i));
		printDouble(static_cast<double>(i), std::numeric_limits<double>::digits10);
	}

	void	convertFromFloat(float f)
	{
		if (fitsChar(f))
			printChar(static_cast<char>(f));
		else
			printImpossible("char");
		if (fitsInt(f))
			printInt(static_cast<int>(f));
		else
			printImpossible("int");
		printFloat(f);
		printDouble(static_cast<double>(f), std::numeric_limits<float>::digits10);
	}

	void	convertFromDouble(double d)
	{
		if (fitsChar(d))
			printChar(static_cast<char>(d));
		else
			printImpossible("char");
		if (fitsInt(d))
			printInt(static_cast<int>(d));
		else
			printImpossible("int");
		if (fitsFloat(d))
			printFloat(static_cast<float>(d));
		else
			printImpossible("float");
		printDouble(d, std::numeric_limits<double>::digits10);
	}
}

// -------------------------------- convert ---------------------------------
// 1. リテラルの型を判定する
// 2. 文字列をその型の値に変換する (その型に収まらなければ全部 impossible)
// 3. 残り 3 つの型へ明示的に変換して表示する

void	ScalarConverter::convert(std::string const &literal)
{
	switch (detectType(literal))
	{
		case TYPE_CHAR:
		{
			// 'a' 形式なら 2 文字目、a 形式なら 1 文字目が値
			convertFromChar(literal.length() == 3 ? literal[1] : literal[0]);
			return ;
		}
		case TYPE_INT:
		{
			int	i;
			if (parseInt(literal, i))
				convertFromInt(i);
			else
				printAllImpossible();
			return ;
		}
		case TYPE_FLOAT:
		{
			float	f;
			if (parseFloat(literal, f))
				convertFromFloat(f);
			else
				printAllImpossible();
			return ;
		}
		case TYPE_DOUBLE:
		{
			double	d;
			if (parseDouble(literal, d))
				convertFromDouble(d);
			else
				printAllImpossible();
			return ;
		}
		case TYPE_INVALID:
			break ;
	}
	printAllImpossible();
}
