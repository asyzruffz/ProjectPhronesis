
#include "StdAfx.hpp"
#include "Game.hpp"

#include "Engine.hpp"
#include "Phronesis/Graphics/Window.hpp"
#include "Phronesis/Graphics/Renderer.hpp"

using namespace Phronesis;

const int Game::WIDTH = 600;
const int Game::HEIGHT = 600;

void Game::run()
{
	init();
	mainLoop();
	dispose();
}

void Game::init()
{
	modules.add<Window>(Module::Stage::Render);
	modules.get<Window>()->init(WIDTH, HEIGHT, "Phronesis - Sandbox (Vulkan)");

	modules.add<Renderer>(Module::Stage::Render);
	modules.get<Renderer>()->init();
}

void Game::mainLoop()
{
	while(Engine::Get()->isRunning())
	{
		modules.updateStage(Module::Stage::Always);

		modules.updateStage(Module::Stage::Pre);
		modules.updateStage(Module::Stage::Normal);
		modules.updateStage(Module::Stage::Post);


		modules.updateStage(Module::Stage::Render);
	}
}

void Game::dispose()
{
	modules.get<Renderer>()->dispose();
	modules.get<Window>()->dispose();
}
