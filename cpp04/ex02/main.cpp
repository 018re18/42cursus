#include "AAnimal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

static void	abstractTest(void)
{
	std::cout << "=== AAnimal is abstract ===" << std::endl;
	std::cout << "The line below does not compile, "
		<< "AAnimal has a pure virtual makeSound():" << std::endl;
	std::cout << "    const AAnimal *meta = new AAnimal();" << std::endl;
	// const AAnimal	*meta = new AAnimal();
	// AAnimal		onTheStack;
	std::cout << std::endl;
}

static void	subjectTest(void)
{
	std::cout << "=== subject test ===" << std::endl;

	const AAnimal	*j = new Dog();
	const AAnimal	*i = new Cat();

	std::cout << std::endl << "--- sounds ---" << std::endl;
	j->makeSound();
	i->makeSound();

	std::cout << std::endl << "--- deletion, no leak ---" << std::endl;
	delete j;
	delete i;
	std::cout << std::endl;
}

static void	arrayTest(void)
{
	std::cout << "=== half dogs, half cats ===" << std::endl;

	const int	size = 8;
	AAnimal		*animals[size];

	for (int k = 0; k < size; k++)
	{
		if (k < size / 2)
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

	std::cout << std::endl << "--- delete them all as AAnimal* ---" << std::endl;
	for (int k = 0; k < size; k++)
		delete animals[k];
	std::cout << std::endl;
}

static void	deepCopyConstructorTest(void)
{
	std::cout << "=== deep copy: copy constructor ===" << std::endl;

	Dog	original;

	original.setIdea(0, "I want a bone");
	original.setIdea(1, "I want a walk");

	std::cout << std::endl << "--- copy ---" << std::endl;
	Dog	copy(original);

	std::cout << std::endl << "--- the copy carries the ideas ---" << std::endl;
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "copy[0]    : " << copy.getIdea(0) << std::endl;

	std::cout << std::endl << "--- brains live at different addresses ---" << std::endl;
	std::cout << "original brain: " << original.getBrain() << std::endl;
	std::cout << "copy brain    : " << copy.getBrain() << std::endl;
	std::cout << "deep copy: "
		<< (original.getBrain() != copy.getBrain() ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- changing the copy leaves the original alone ---"
		<< std::endl;
	copy.setIdea(0, "I want two bones");
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "copy[0]    : " << copy.getIdea(0) << std::endl;
	std::cout << "independent: "
		<< (original.getIdea(0) != copy.getIdea(0) ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- destruction ---" << std::endl;
}

static void	deepCopyAssignmentTest(void)
{
	std::cout << "=== deep copy: assignment operator ===" << std::endl;

	Cat	original;
	Cat	assigned;

	original.setIdea(0, "I want a nap");
	assigned.setIdea(0, "I want nothing");

	std::cout << std::endl << "--- assignment ---" << std::endl;
	assigned = original;

	std::cout << std::endl << "--- result ---" << std::endl;
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "assigned[0]: " << assigned.getIdea(0) << std::endl;
	std::cout << "original brain: " << original.getBrain() << std::endl;
	std::cout << "assigned brain: " << assigned.getBrain() << std::endl;
	std::cout << "deep copy: "
		<< (original.getBrain() != assigned.getBrain() ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- changing the original leaves the copy alone ---"
		<< std::endl;
	original.setIdea(0, "I want two naps");
	std::cout << "original[0]: " << original.getIdea(0) << std::endl;
	std::cout << "assigned[0]: " << assigned.getIdea(0) << std::endl;
	std::cout << "independent: "
		<< (original.getIdea(0) != assigned.getIdea(0) ? "OK" : "KO") << std::endl;

	std::cout << std::endl << "--- self assignment is harmless ---" << std::endl;
	Cat	&alias = assigned;

	assigned = alias;
	std::cout << "assigned[0]: " << assigned.getIdea(0) << std::endl;

	std::cout << std::endl << "--- destruction ---" << std::endl;
}

static void	brainBoundsTest(void)
{
	std::cout << "=== Brain bounds ===" << std::endl;

	Brain	brain;

	std::cout << std::endl;
	brain.setIdea(99, "the last idea");
	std::cout << "idea 99 : " << brain.getIdea(99) << std::endl;
	brain.setIdea(100, "one idea too many");
	std::cout << "idea 100: " << brain.getIdea(100) << std::endl;
	brain.setIdea(-1, "one idea too few");
	std::cout << "idea -1 : " << brain.getIdea(-1) << std::endl;

	std::cout << std::endl << "--- destruction ---" << std::endl;
}

int	main(void)
{
	abstractTest();
	subjectTest();
	arrayTest();
	deepCopyConstructorTest();
	std::cout << std::endl;
	deepCopyAssignmentTest();
	std::cout << std::endl;
	brainBoundsTest();
	std::cout << std::endl;
	return (0);
}
