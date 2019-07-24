
#include "StdAfx.hpp"
#include "Game.hpp"

#include "Engine.hpp"
#include "Phronesis/Graphics/Window.hpp"
#include "Phronesis/Graphics/Renderer.hpp"

using namespace Phronesis;

const int Game::WIDTH = 600;
const int Game::HEIGHT = 600;

Game::Game() :
	fpsLimit(-1.0f),
	elapsedRender(Time::Seconds(-1.0f)),
	elapsedUpdate(Time::Microseconds(14705))
{
}

void Game::run()
{
	init();
	mainLoop();
	dispose();
}

void Game::init()
{
	elapsedUpdate.start();
	elapsedRender.start();

	modules.add<Window>(Module::Stage::Pre);
	modules.get<Window>()->init(WIDTH, HEIGHT, "Phronesis - Sandbox (Vulkan)");

	modules.add<Renderer>(Module::Stage::Render);
	modules.get<Renderer>()->init();
}

void Game::mainLoop()
{
	while(Engine::Get()->isRunning())
	{
		elapsedRender.setInterval(Time::Seconds(1.0f / fpsLimit));

		// always update.
		modules.updateStage(Module::Stage::Always);

		if(elapsedUpdate.getElapsed() != 0)
		{
			modules.updateStage(Module::Stage::Pre);
			modules.updateStage(Module::Stage::Normal);
			modules.updateStage(Module::Stage::Post);
		}

		if(elapsedRender.getElapsed() != 0)
		{
			modules.updateStage(Module::Stage::Render);
		}
	}
}

void Game::dispose()
{
	modules.get<Renderer>()->dispose();
	modules.get<Window>()->dispose();
}
