#include "identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

static void	check(Base *p)
{
	std::cout << "  identify(Base *) : ";
	identify(p);
	std::cout << "  identify(Base &) : ";
	identify(*p);
}

int	main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "--- random ---" << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		Base	*p = generate();

		std::cout << "#" << i << std::endl;
		check(p);
		delete p;
	}

	std::cout << "--- fixed ---" << std::endl;
	Base	*fixed[3] = { new A(), new B(), new C() };
	char const	*names[3] = { "A", "B", "C" };
	for (int i = 0; i < 3; ++i)
	{
		std::cout << "new " << names[i] << "()" << std::endl;
		check(fixed[i]);
		delete fixed[i];
	}

	std::cout << "--- NULL ---" << std::endl;
	std::cout << "  identify(Base *) : ";
	identify(static_cast<Base *>(NULL));
	return (0);
}
