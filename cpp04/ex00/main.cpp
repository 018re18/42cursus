#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

static void	subjectTest(void)
{
	std::cout << "=== subject test ===" << std::endl;

	const Animal	*meta = new Animal();
	const Animal	*j = new Dog();
	const Animal	*i = new Cat();

	std::cout << std::endl << "--- types ---" << std::endl;
	std::cout << meta->getType() << " " << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	std::cout << std::endl << "--- sounds through Animal* ---" << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	std::cout << std::endl << "--- deletion through Animal* ---" << std::endl;
	delete meta;
	delete j;
	delete i;
	std::cout << std::endl;
}

static void	wrongTest(void)
{
	std::cout << "=== wrong test ===" << std::endl;

	const WrongAnimal	*meta = new WrongAnimal();
	const WrongAnimal	*i = new WrongCat();

	std::cout << std::endl << "--- types ---" << std::endl;
	std::cout << meta->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	std::cout << std::endl << "--- sounds through WrongAnimal* ---" << std::endl;
	i->makeSound();
	meta->makeSound();
	std::cout << "(the WrongCat sound is never heard: makeSound is not virtual)"
		<< std::endl;

	std::cout << std::endl << "--- sound through the real type ---" << std::endl;
	const WrongCat	realCat;

	realCat.makeSound();

	std::cout << std::endl << "--- deletion ---" << std::endl;
	delete meta;
	delete static_cast<const WrongCat *>(i);
	std::cout << std::endl;
}

static void	arrayTest(void)
{
	std::cout << "=== polymorphic array ===" << std::endl;

	const int	size = 6;
	Animal		*animals[size];

	for (int k = 0; k < size; k++)
	{
		if (k % 2 == 0)
			animals[k] = new Dog();
		else
			animals[k] = new Cat();
	}

	std::cout << std::endl << "--- each animal speaks ---" << std::endl;
	for (int k = 0; k < size; k++)
	{
		std::cout << "[" << k << "] " << animals[k]->getType() << ": ";
		animals[k]->makeSound();
	}

	std::cout << std::endl << "--- delete them all as Animal* ---" << std::endl;
	for (int k = 0; k < size; k++)
		delete animals[k];
	std::cout << std::endl;
}

static void	copyTest(void)
{
	std::cout << "=== copy semantics ===" << std::endl;

	Dog	original;

	std::cout << std::endl << "--- copy construction ---" << std::endl;
	Dog	copy(original);

	std::cout << std::endl << "--- copy assignment ---" << std::endl;
	Dog	assigned;

	assigned = original;

	std::cout << std::endl << "--- the copies behave like dogs ---" << std::endl;
	std::cout << copy.getType() << ": ";
	copy.makeSound();
	std::cout << assigned.getType() << ": ";
	assigned.makeSound();

	std::cout << std::endl << "--- destruction ---" << std::endl;
}

static void	sliceTest(void)
{
	std::cout << "=== reference to base, no slicing ===" << std::endl;

	Cat				cat;
	Animal			&ref = cat;
	Animal const	&constRef = cat;

	std::cout << std::endl;
	std::cout << "ref (" << ref.getType() << "): ";
	ref.makeSound();
	std::cout << "constRef (" << constRef.getType() << "): ";
	constRef.makeSound();

	std::cout << std::endl << "--- destruction ---" << std::endl;
}

int	main(void)
{
	subjectTest();
	wrongTest();
	arrayTest();
	copyTest();
	std::cout << std::endl;
	sliceTest();
	std::cout << std::endl;
	return (0);
}
