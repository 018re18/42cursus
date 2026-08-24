#include "ScavTrap.hpp"

// -------------------------------- 正準形 ----------------------------------

void	ScavTrap::_initStats(void)
{
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
}

ScavTrap::ScavTrap(void) : ClapTrap()
{
	this->_initStats();
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string const &name) : ClapTrap(name)
{
	this->_initStats();
	std::cout << "ScavTrap " << this->_name << " constructor called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &src) : ClapTrap(src)
{
	std::cout << "ScavTrap copy constructor called" << std::endl;
	*this = src;
}

// ScavTrap は自前のメンバを持たないので、基底クラスに丸ごと任せる。
ScavTrap &ScavTrap::operator=(ScavTrap const &rhs)
{
	std::cout << "ScavTrap copy assignment operator called" << std::endl;
	if (this != &rhs)
		ClapTrap::operator=(rhs);
	return (*this);
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap " << this->_name << " destructor called" << std::endl;
}

// --------------------------------- 行動 -----------------------------------

// エネルギーの確認は ClapTrap と同じ。表示するメッセージだけが違う。
void	ScavTrap::attack(std::string const &target)
{
	if (!this->_consumeEnergy("ScavTrap", "attack"))
		return ;
	std::cout << "ScavTrap " << this->_name << " viciously bites " << target
		<< ", causing " << this->_attackDamage << " points of damage!"
		<< std::endl;
}

void	ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << this->_name
		<< " is now in Gate keeper mode!" << std::endl;
}
