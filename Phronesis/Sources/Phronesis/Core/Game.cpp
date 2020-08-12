
#include "StdAfx.hpp"
#include "Game.hpp"

#include "Engine.hpp"
#include "Phronesis/Graphics/Window.hpp"
#include "Phronesis/Graphics/Renderer.hpp"
#include "Phronesis/SceneManagement/Scenes.hpp"

using namespace Phronesis;

const int Game::WIDTH = 600;
const int Game::HEIGHT = 600;

Game::Game(const char* title) :
	title(title),
	fpsLimit(-1.0f),
	elapsedFPS(Time::Seconds(1.0f)),
	elapsedRender(Time::Seconds(-1.0f)),
	elapsedPhysics(Time::Seconds(0.02f)),
	elapsedUpdate(Time::Seconds(-1.0f))//Time::Microseconds(14705)) // ~60FPS
{
}

void Game::run()
{
	init();
	mainLoop();
	dispose();
}

const Time& Game::getDeltaTime() const
{
	return deltaUpdate.getChange();
}

const unsigned int& Game::getUps() const
{
	return ups.getValue();
}

const unsigned int& Game::getFps() const
{
	return fps.getValue();
}

void Game::init()
{
	elapsedUpdate.start();
	elapsedRender.start();

	modules.add<Window>(Module::Stage::Pre);
	Log::info("Window module added");
	modules.add<Scenes>(Module::Stage::Normal);
	Log::info("Scenes module added");
	modules.add<Renderer>(Module::Stage::Render);
	Log::info("Renderer module added");

	modules.get<Window>()->init(WIDTH, HEIGHT, title);
	modules.get<Scenes>()->init();
	modules.get<Renderer>()->init();
}

void Game::mainLoop()
{
	while(Engine::Get()->isRunning())
	{
		elapsedRender.setInterval(Time::Seconds(1.0f / fpsLimit));

		// always update.
		modules.updateStage(Module::Stage::Always);

		if(elapsedFPS.getElapsed() != 0)
		{
			Log::debug("UPS: {}, FPS: {}", ups.getValue(), fps.getValue());
		}

		if(elapsedUpdate.getElapsed() != 0)
		{
			ups.update(Time::now());

			modules.updateStage(Module::Stage::Pre);
			modules.updateStage(Module::Stage::Normal);
			modules.updateStage(Module::Stage::Post);

			deltaUpdate.update();
		}

		if(elapsedPhysics.getElapsed() != 0)
		{
			modules.updateStage(Module::Stage::Physics);
		}

		// prioritize updates over rendering
		if((elapsedUpdate.getInterval().asSeconds() - deltaUpdate.getChange().asSeconds()) > 0.8f)
		{
			continue;
		}

		if(elapsedRender.getElapsed() != 0)
		{
			fps.update(Time::now());

			modules.updateStage(Module::Stage::Render);
		}
	}
}

void Game::dispose()
{
	modules.get<Renderer>()->dispose();
	modules.get<Scenes>()->dispose();
	modules.get<Window>()->dispose();
	
	modules.remove<Renderer>();
	Log::info("Renderer module removed");
	modules.remove<Scenes>();
	Log::info("Scenes module removed");
	modules.remove<Window>();
	Log::info("Window module removed");
}
