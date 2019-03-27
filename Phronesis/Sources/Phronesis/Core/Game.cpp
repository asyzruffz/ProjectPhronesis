
#include "Game.hpp"

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
	renderer = new Renderer;

	renderer->initWindow(WIDTH, HEIGHT, "Phronesis - Test Game (Vulkan)");
	renderer->initVulkan();
}

void Game::mainLoop()
{
	renderer->update();
}

void Game::dispose()
{
	renderer->disposeVulkan();
	renderer->disposeWindow();
	delete renderer;
}
