#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

// 日付ごとのビットコイン価格データベース (CSV) を保持し、
// 入力ファイルの "date | value" を評価額に換算して出力する。
class BitcoinExchange
{
	private:
		// キーは "YYYY-MM-DD" 形式の日付。
		// ゼロ埋め固定長なので、文字列の辞書順がそのまま日付順になる
		std::map<std::string, double>	_rates;

		void	_loadDatabase(std::string const &filename);
		void	_processLine(std::string const &line) const;

		static bool	_isValidDate(std::string const &date);
		static bool	_parseNumber(std::string const &str, double &out);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange const &src);
		BitcoinExchange &operator=(BitcoinExchange const &rhs);
		~BitcoinExchange(void);

		// データベースを読み込む。開けない・形式が不正なら例外を投げる
		explicit BitcoinExchange(std::string const &dbFilename);

		// 入力ファイルを 1 行ずつ評価して標準出力に書き出す。
		// ファイル自体が開けない場合のみ例外を投げ、行単位のエラーはその場で出力する
		void	processInput(std::string const &filename) const;
};

#endif
