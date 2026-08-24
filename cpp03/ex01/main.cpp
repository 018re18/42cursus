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

	std::cout << std::endl << "=== ScavTrap: コンストラクタの連鎖 ===" << std::endl;
	{
		ScavTrap	scavy("SC4V-TP");

		std::cout << std::endl << "--- 行動 ---" << std::endl;
		scavy.attack("Bandit");
		scavy.takeDamage(30);
		scavy.beRepaired(10);
		scavy.guardGate();

		std::cout << std::endl << "--- デストラクタの連鎖 ---" << std::endl;
	}

	std::cout << std::endl << "=== ScavTrap: コピーの挙動 ===" << std::endl;
	{
		ScavTrap	original("Original");
		ScavTrap	copy(original);
		ScavTrap	assigned("Assigned");

		assigned = original;
		copy.attack("Bandit");
		assigned.guardGate();
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== ScavTrap: エネルギー切れ ===" << std::endl;
	{
		ScavTrap	tired("Tired");

		for (int i = 0; i < 51; i++)
			tired.attack("Bandit");
		tired.beRepaired(1);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== 基底クラスのポインタ越しの多態 ===" << std::endl;
	{
		ClapTrap	*bot = new ScavTrap("Polymorphic");

		bot->attack("Bandit");
		delete bot;
	}
	return (0);
}
