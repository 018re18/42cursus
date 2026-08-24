#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

// 門番型の ClapTrap。ステータスが高く、攻撃の見た目も専用のものになる。
class ScavTrap : public ClapTrap
{
	private:
		// ScavTrap 固有の初期ステータスを入れ直す。
		// ClapTrap のコンストラクタが先に走るので、その後で上書きする。
		void	_initStats(void);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		ScavTrap(void);
		ScavTrap(ScavTrap const &src);
		ScavTrap &operator=(ScavTrap const &rhs);
		virtual ~ScavTrap(void);

		ScavTrap(std::string const &name);

		virtual void	attack(std::string const &target);
		void			guardGate(void);
};

#endif
