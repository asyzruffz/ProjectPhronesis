
#include <cstdlib>
#include <iostream>

#include "Engine.hpp"
using namespace Phronesis;


Engine::Engine(char** argv, int argc)
{
	args.resize(argc); // convert arguments to string vector
	for(int i = 0; i < argc; i++)
	{
		args[i] = argv[i];
	}
}

Engine::~Engine()
{
}

void Engine::setGame(Game* newGame)
{
	game = std::unique_ptr<Game>(newGame);
}

void Engine::run()
{
	if(game) game->run();
}
