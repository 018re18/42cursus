#include "ClapTrap.hpp"

// -------------------------------- 正準形 ----------------------------------

ClapTrap::ClapTrap(void)
	: _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string const &name)
	: _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << this->_name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &src)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = src;
}

ClapTrap &ClapTrap::operator=(ClapTrap const &rhs)
{
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_hitPoints = rhs._hitPoints;
		this->_energyPoints = rhs._energyPoints;
		this->_attackDamage = rhs._attackDamage;
	}
	return (*this);
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap " << this->_name << " destructor called" << std::endl;
}

// --------------------------------- 行動 -----------------------------------

bool	ClapTrap::_consumeEnergy(std::string const &type,
			std::string const &action)
{
	if (this->_hitPoints == 0)
	{
		std::cout << type << " " << this->_name
			<< " has no hit points left and cannot " << action << "..."
			<< std::endl;
		return (false);
	}
	if (this->_energyPoints == 0)
	{
		std::cout << type << " " << this->_name
			<< " has no energy points left and cannot " << action << "..."
			<< std::endl;
		return (false);
	}
	this->_energyPoints--;
	return (true);
}

void	ClapTrap::attack(std::string const &target)
{
	if (!this->_consumeEnergy("ClapTrap", "attack"))
		return ;
	std::cout << "ClapTrap " << this->_name << " attacks " << target
		<< ", causing " << this->_attackDamage << " points of damage!"
		<< std::endl;
}

// ダメージを受けるのにエネルギーは要らないので、体力だけを確認する。
void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hitPoints == 0)
	{
		std::cout << "ClapTrap " << this->_name
			<< " is already down and takes no more damage..." << std::endl;
		return ;
	}
	// _hitPoints は unsigned なので、引き算で 0 を下回らせないようにする
	if (amount >= this->_hitPoints)
		this->_hitPoints = 0;
	else
		this->_hitPoints -= amount;
	std::cout << "ClapTrap " << this->_name << " takes " << amount
		<< " points of damage! Hit points left: " << this->_hitPoints
		<< std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (!this->_consumeEnergy("ClapTrap", "be repaired"))
		return ;
	this->_hitPoints += amount;
	std::cout << "ClapTrap " << this->_name << " repairs itself for " << amount
		<< " hit points! Hit points left: " << this->_hitPoints << std::endl;
}

// -------------------------------- ゲッター ---------------------------------

std::string const	&ClapTrap::getName(void) const
{
	return (this->_name);
}

unsigned int	ClapTrap::getHitPoints(void) const
{
	return (this->_hitPoints);
}

unsigned int	ClapTrap::getEnergyPoints(void) const
{
	return (this->_energyPoints);
}

unsigned int	ClapTrap::getAttackDamage(void) const
{
	return (this->_attackDamage);
}
