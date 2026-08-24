#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <string>

// 名前・体力・エネルギー・攻撃力を持つロボット。
// 体力 (_hitPoints) が 0 になると何もできなくなり、
// 攻撃と修理は 1 回につきエネルギー (_energyPoints) を 1 消費する。
class ClapTrap
{
	private:
		std::string		_name;
		unsigned int	_hitPoints;
		unsigned int	_energyPoints;
		unsigned int	_attackDamage;

		// 行動できるかを確かめる。行動できるならエネルギーを 1 消費して
		// true を返し、できないなら理由を表示して false を返す。
		// type は表示に使うクラス名、action は行動の名前 ("attack" など)。
		bool	_consumeEnergy(std::string const &type,
					std::string const &action);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		ClapTrap(void);
		ClapTrap(ClapTrap const &src);
		ClapTrap &operator=(ClapTrap const &rhs);
		~ClapTrap(void);

		ClapTrap(std::string const &name);

		// 行動
		void	attack(std::string const &target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		std::string const	&getName(void) const;
		unsigned int		getHitPoints(void) const;
		unsigned int		getEnergyPoints(void) const;
		unsigned int		getAttackDamage(void) const;
};

#endif
