// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdexcept>
#include <cstdlib> // provide EXIT_SUCCESS

#include "Phronesis/Core.hpp"
#include "Core/SandboxGame.hpp"

int main(int argc, char **argv)
{
	try {
		Phronesis::Engine engine(argv, argc);
		engine.setGame(new SandboxGame());
		engine.run();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

