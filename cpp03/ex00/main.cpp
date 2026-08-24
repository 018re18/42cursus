#include "ClapTrap.hpp"

int	main(void)
{
	std::cout << "=== construction ===" << std::endl;
	ClapTrap	clappy("CL4P-TP");
	ClapTrap	target("Target");

	std::cout << std::endl << "=== basic actions ===" << std::endl;
	clappy.attack("Target");
	target.takeDamage(4);
	target.beRepaired(2);

	std::cout << std::endl << "=== copy semantics ===" << std::endl;
	ClapTrap	copy(clappy);
	copy.attack("Target");

	ClapTrap	assigned("Assigned");
	assigned = clappy;
	assigned.attack("Target");

	std::cout << std::endl << "=== energy exhaustion ===" << std::endl;
	ClapTrap	tired("Tired");
	for (int i = 0; i < 11; i++)
		tired.attack("Target");
	tired.beRepaired(5);

	std::cout << std::endl << "=== death ===" << std::endl;
	ClapTrap	dead("Dead");
	dead.takeDamage(100);
	dead.takeDamage(1);
	dead.attack("Target");
	dead.beRepaired(10);

	std::cout << std::endl << "=== destruction ===" << std::endl;
	return (0);
}
