
#include "StdAfx.hpp"
#include "Engine.hpp"

#include "Game.hpp"

using namespace Phronesis;


Engine* Engine::instance = nullptr;
Engine* Engine::Get()
{
	return instance;
}

Engine::Engine(char** argv, int argc)
	: game(nullptr), running(false)
{
	instance = this;
	Log::init();

	args.resize(argc); // convert arguments to string vector
	for(int i = 0; i < argc; i++)
	{
		args[i] = argv[i];
	}
}

Engine::~Engine()
{
	// TODO: kill thread
	instance = nullptr;
}

void Engine::setGame(Game* newGame)
{
	game.reset(newGame);
}

Game& Engine::getGame()
{
	return *(game.get());
}

void Engine::run()
{
	try {
		// TODO: implement multi-threading
		running = true;
		if(game) game->run();
		running = false;
	}
	catch(const std::exception& e)
	{
		running = false;
		Log::error(e.what());
		throw;
	}
}

bool Engine::isRunning() const
{
	return running;
}

void Engine::stop()
{
	running = false;
}
