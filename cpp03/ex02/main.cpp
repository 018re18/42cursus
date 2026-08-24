#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int	main(void)
{
	std::cout << "=== ClapTrap ===" << std::endl;
	{
		ClapTrap	clappy("CL4P-TP");

		clappy.attack("Bandit");
		clappy.takeDamage(3);
		clappy.beRepaired(2);
	}

	std::cout << std::endl << "=== ScavTrap ===" << std::endl;
	{
		ScavTrap	scavy("SC4V-TP");

		scavy.attack("Bandit");
		scavy.takeDamage(30);
		scavy.beRepaired(10);
		scavy.guardGate();
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== FragTrap: コンストラクタの連鎖 ===" << std::endl;
	{
		FragTrap	fraggy("FR4G-TP");

		std::cout << std::endl << "--- 行動 ---" << std::endl;
		fraggy.attack("Bandit");
		fraggy.takeDamage(40);
		fraggy.beRepaired(15);
		fraggy.highFivesGuys();

		std::cout << std::endl << "--- デストラクタの連鎖 ---" << std::endl;
	}

	std::cout << std::endl << "=== FragTrap: コピーの挙動 ===" << std::endl;
	{
		FragTrap	original("Original");
		FragTrap	copy(original);
		FragTrap	assigned("Assigned");

		assigned = original;
		copy.highFivesGuys();
		assigned.attack("Bandit");
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== FragTrap: 体力 0 ===" << std::endl;
	{
		FragTrap	doomed("Doomed");

		doomed.takeDamage(100);
		doomed.takeDamage(10);
		doomed.attack("Bandit");
		doomed.beRepaired(50);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== それぞれが自分の attack を使う ===" << std::endl;
	{
		ClapTrap	*bots[3];

		bots[0] = new ClapTrap("Base");
		bots[1] = new ScavTrap("Scav");
		bots[2] = new FragTrap("Frag");
		std::cout << std::endl;
		for (int i = 0; i < 3; i++)
			bots[i]->attack("Bandit");
		std::cout << std::endl;
		for (int i = 0; i < 3; i++)
			delete bots[i];
	}
	return (0);
}
