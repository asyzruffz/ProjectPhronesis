// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdexcept>
#include <cstdlib> // provide EXIT_SUCCESS

#include "Phronesis.hpp"


int main(int argc, char **argv)
{
	//Phronesis::Engine engine;
	//engine.test();

	Phronesis::Game game;

	try {
		game.run();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

