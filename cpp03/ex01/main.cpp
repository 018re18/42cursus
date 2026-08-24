#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	std::cout << "=== ClapTrap ===" << std::endl;
	{
		ClapTrap	clappy("CL4P-TP");

		clappy.attack("Bandit");
		clappy.takeDamage(3);
		clappy.beRepaired(2);
	}

	std::cout << std::endl << "=== ScavTrap: construction chaining ===" << std::endl;
	{
		ScavTrap	scavy("SC4V-TP");

		std::cout << std::endl << "--- actions ---" << std::endl;
		scavy.attack("Bandit");
		scavy.takeDamage(30);
		scavy.beRepaired(10);
		scavy.guardGate();

		std::cout << std::endl << "--- destruction chaining ---" << std::endl;
	}

	std::cout << std::endl << "=== ScavTrap: copy semantics ===" << std::endl;
	{
		ScavTrap	original("Original");
		ScavTrap	copy(original);
		ScavTrap	assigned("Assigned");

		assigned = original;
		copy.attack("Bandit");
		assigned.guardGate();
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== ScavTrap: energy exhaustion ===" << std::endl;
	{
		ScavTrap	tired("Tired");

		for (int i = 0; i < 51; i++)
			tired.attack("Bandit");
		tired.beRepaired(1);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== polymorphism through base pointer ===" << std::endl;
	{
		ClapTrap	*bot = new ScavTrap("Polymorphic");

		bot->attack("Bandit");
		delete bot;
	}
	return (0);
}
