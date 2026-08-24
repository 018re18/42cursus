#include "ClapTrap.hpp"

int	main(void)
{
	std::cout << "=== 生成 ===" << std::endl;
	ClapTrap	clappy("CL4P-TP");
	ClapTrap	target("Target");

	std::cout << std::endl << "=== 基本の行動 ===" << std::endl;
	clappy.attack("Target");
	target.takeDamage(4);
	target.beRepaired(2);

	std::cout << std::endl << "=== コピーの挙動 ===" << std::endl;
	ClapTrap	copy(clappy);
	copy.attack("Target");

	ClapTrap	assigned("Assigned");
	assigned = clappy;
	assigned.attack("Target");

	std::cout << std::endl << "=== エネルギー切れ ===" << std::endl;
	ClapTrap	tired("Tired");
	for (int i = 0; i < 11; i++)
		tired.attack("Target");
	tired.beRepaired(5);

	std::cout << std::endl << "=== 体力 0 ===" << std::endl;
	ClapTrap	dead("Dead");
	dead.takeDamage(100);
	dead.takeDamage(1);
	dead.attack("Target");
	dead.beRepaired(10);

	std::cout << std::endl << "=== 破棄 ===" << std::endl;
	return (0);
}
