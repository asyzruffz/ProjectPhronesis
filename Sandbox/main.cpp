// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdexcept>
#include <cstdlib> // provide EXIT_SUCCESS

#include "Phronesis/Core.hpp"


int main(int argc, char **argv)
{
	try {
		Phronesis::Engine engine(argv, argc);

		game.run();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

