// main.cpp : Defines the entry point for the console application.
//

#include "StdAfx.hpp"

#include "SandboxGame.hpp"

int main(int argc, char** argv)
{
	try {
		Phronesis::Engine engine(argv, argc);
		engine.setGame(new SandboxGame("Phronesis - Sandbox (SFML)"));
		engine.run();
	}
	catch(const std::exception& e) {
		std::cerr << "[ERROR] " << e.what() << std::endl;
		//system("pause");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
