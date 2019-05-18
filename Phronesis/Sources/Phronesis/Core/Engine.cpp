
#include "StdAfx.hpp"
#include "Engine.hpp"

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

	// Log testing
	Log::info("Info test!");
	Log::error("Error test!");
	Log::debug("Debug test!");
	Log::echo("Echo test!");
	Log::print("Print test!");
}

Engine::~Engine()
{
	// TODO: kill thread
	instance = nullptr;
}

void Engine::setGame(Game* newGame)
{
	game = std::unique_ptr<Game>(newGame);
}

void Engine::run()
{
	running = true;

	// TODO: implement multi-threading
	if(game) game->run();
}

bool Engine::isRunning() const
{
	return running;
}

void Engine::stop()
{
	running = false;
}
