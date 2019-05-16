
#include "StdAfx.hpp"
#include "Game.hpp"

#include "Engine.hpp"
#include "Phronesis/Graphics/Renderer.hpp"

using namespace Phronesis;

const int Game::WIDTH = 800;
const int Game::HEIGHT = 600;

void Game::run()
{
	init();
	mainLoop();
	dispose();
}

void Game::init()
{
	modules.add<Renderer>(Module::Stage::Render);

	modules.get<Renderer>()->initWindow(WIDTH, HEIGHT, "Phronesis - Sandbox (Vulkan)");
	modules.get<Renderer>()->initVulkan();
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
	modules.get<Renderer>()->disposeVulkan();
	modules.get<Renderer>()->disposeWindow();
}
