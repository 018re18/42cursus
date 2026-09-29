#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
	: _rates(src._rates)
{
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
		this->_rates = rhs._rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(std::string const &dbFilename)
{
	this->_loadDatabase(dbFilename);
}

// 行末の '\r' を取り除く (CRLF 改行のファイル対策)
static void	stripCarriageReturn(std::string &line)
{
	if (!line.empty() && line[line.size() - 1] == '\r')
		line.erase(line.size() - 1);
}

void	BitcoinExchange::_loadDatabase(std::string const &filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file.is_open())
		throw std::runtime_error("could not open database.");
	if (!std::getline(file, line))
		throw std::runtime_error("database is empty or unreadable.");
	stripCarriageReturn(line);
	if (line != "date,exchange_rate")
		throw std::runtime_error("invalid database header => " + line);
	while (std::getline(file, line))
	{
		stripCarriageReturn(line);
		if (line.empty())
			continue ;

		std::string::size_type	comma = line.find(',');
		double					rate;

		if (comma == std::string::npos
			|| !_isValidDate(line.substr(0, comma))
			|| !_parseNumber(line.substr(comma + 1), rate)
			|| rate < 0)
			throw std::runtime_error("invalid database line => " + line);
		this->_rates[line.substr(0, comma)] = rate;
	}
	if (this->_rates.empty())
		throw std::runtime_error("database has no entries.");
}

void	BitcoinExchange::processInput(std::string const &filename) const
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file.is_open())
		throw std::runtime_error("could not open file.");
	// 既定の有効桁数 6 だと 1000 * 47115.93 が 4.71159e+07 と指数表記になるため桁数を増やす。
	// double の誤差 (17 桁目付近) は表に出ない桁数に抑えている
	std::cout.precision(10);
	// 1 行も読めない場合はエラーにする。空ファイルのほか、ディレクトリを渡された場合も
	// open 自体は成功して読み込みで失敗するため、ここで検出する
	if (!std::getline(file, line))
		throw std::runtime_error("empty or unreadable file.");
	// 1 行目がヘッダならスキップ。ヘッダでなければ通常のデータ行として扱う
	stripCarriageReturn(line);
	if (line != "date | value")
		this->_processLine(line);
	while (std::getline(file, line))
	{
		stripCarriageReturn(line);
		this->_processLine(line);
	}
}

// 行単位のエラーは、結果の行と順序が崩れないよう標準出力に出す
void	BitcoinExchange::_processLine(std::string const &line) const
{
	std::string::size_type	sep = line.find(" | ");

	if (sep == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}

	std::string const	date = line.substr(0, sep);
	double				value;

	if (!_isValidDate(date) || !_parseNumber(line.substr(sep + 3), value))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return ;
	}
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return ;
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return ;
	}

	// upper_bound は「date より後」の最初の要素を返すので、その 1 つ前が
	// 「date 以下で最も近い日付」になる。先頭なら DB より前の日付でレートがない
	std::map<std::string, double>::const_iterator	it = this->_rates.upper_bound(date);

	if (it == this->_rates.begin())
	{
		std::cout << "Error: no exchange rate before this date => " << date << std::endl;
		return ;
	}
	--it;
	std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}

static bool	isLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

// "YYYY-MM-DD" 形式で、かつ暦上存在する日付かを判定する
bool	BitcoinExchange::_isValidDate(std::string const &date)
{
	static int const	daysInMonth[12] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	for (std::string::size_type i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue ;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}

	int const	year = std::atoi(date.substr(0, 4).c_str());
	int const	month = std::atoi(date.substr(5, 2).c_str());
	int const	day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12 || day < 1)
		return (false);
	if (month == 2 && isLeapYear(year))
		return (day <= 29);
	return (day <= daysInMonth[month - 1]);
}

// [-]digits[.digits] の形式だけを数値として受け付ける。
// strtod 単体だと "1e3" や "inf", "0x10" まで通してしまうので、先に形式を検査する
bool	BitcoinExchange::_parseNumber(std::string const &str, double &out)
{
	std::string::size_type	i = 0;
	std::string::size_type	digits = 0;

	if (i < str.size() && str[i] == '-')
		++i;
	while (i < str.size() && std::isdigit(static_cast<unsigned char>(str[i])))
	{
		++i;
		++digits;
	}
	if (digits == 0)
		return (false);
	if (i < str.size() && str[i] == '.')
	{
		++i;
		digits = 0;
		while (i < str.size() && std::isdigit(static_cast<unsigned char>(str[i])))
		{
			++i;
			++digits;
		}
		if (digits == 0)
			return (false);
	}
	if (i != str.size())
		return (false);
	out = std::strtod(str.c_str(), NULL);
	// "-0" や "-0.0" は -0.0 になり、そのままだと "-0" と表示されるので 0 に揃える
	if (out == 0)
		out = 0;
	return (true);
}
