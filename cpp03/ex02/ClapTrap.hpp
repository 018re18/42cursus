#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <string>

// ClapTrap 一族の土台になるロボット。
// 体力 (_hitPoints) が 0 になると何もできなくなり、
// 攻撃と修理は 1 回につきエネルギー (_energyPoints) を 1 消費する。
class ClapTrap
{
	protected:
		std::string		_name;
		unsigned int	_hitPoints;
		unsigned int	_energyPoints;
		unsigned int	_attackDamage;

		// 行動できるかを確かめる。行動できるならエネルギーを 1 消費して
		// true を返し、できないなら理由を表示して false を返す。
		// type は表示に使うクラス名 ("ClapTrap" など)、
		// action は行動の名前 ("attack" など)。
		bool	_consumeEnergy(std::string const &type,
					std::string const &action);

	public:
		// 直交正準形 (Orthodox Canonical Form)
		ClapTrap(void);
		ClapTrap(ClapTrap const &src);
		ClapTrap &operator=(ClapTrap const &rhs);
		// 派生クラスを ClapTrap* 経由で delete できるよう virtual にしている
		virtual ~ClapTrap(void);

		ClapTrap(std::string const &name);

		// 行動。attack は派生クラスごとに振る舞いが変わる
		virtual void	attack(std::string const &target);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);

		std::string const	&getName(void) const;
		unsigned int		getHitPoints(void) const;
		unsigned int		getEnergyPoints(void) const;
		unsigned int		getAttackDamage(void) const;
};

#endif
