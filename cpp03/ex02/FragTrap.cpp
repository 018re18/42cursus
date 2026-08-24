#include "FragTrap.hpp"

// -------------------------------- 正準形 ----------------------------------

void	FragTrap::_initStats(void)
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(void) : ClapTrap()
{
	this->_initStats();
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(std::string const &name) : ClapTrap(name)
{
	this->_initStats();
	std::cout << "FragTrap " << this->_name << " constructor called" << std::endl;
}

FragTrap::FragTrap(FragTrap const &src) : ClapTrap(src)
{
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = src;
}

// FragTrap は自前のメンバを持たないので、基底クラスに丸ごと任せる。
FragTrap &FragTrap::operator=(FragTrap const &rhs)
{
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	if (this != &rhs)
		ClapTrap::operator=(rhs);
	return (*this);
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap " << this->_name << " destructor called" << std::endl;
}

// --------------------------------- 行動 -----------------------------------

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->_name
		<< " requests a positive high five! \\o/ Come on guys, don't leave me hanging!"
		<< std::endl;
}
