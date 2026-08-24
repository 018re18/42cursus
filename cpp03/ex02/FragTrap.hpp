#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

// 陽気な ClapTrap。attack は上書きせず ClapTrap のものをそのまま使い、
// 代わりにハイタッチを要求する動作を足している。
class FragTrap : public ClapTrap
{
	private:
		// FragTrap 固有の初期ステータスを入れ直す
		void	_initStats(void);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		FragTrap(void);
		FragTrap(FragTrap const &src);
		FragTrap &operator=(FragTrap const &rhs);
		virtual ~FragTrap(void);

		FragTrap(std::string const &name);

		void	highFivesGuys(void);
};

#endif
