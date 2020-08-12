
#include "StdAfx.hpp"
#include "Scenes.hpp"

using namespace Phronesis;

void Scenes::init()
{
	currentScene = nullptr;
}

void Scenes::update()
{
	if(currentScene == nullptr)
	{
		return;
	}

	if(!currentScene->hasStarted())
	{
		currentScene->internalStart();
		currentScene->setStarted();
	}

	currentScene->internalUpdate();
}

void Scenes::dispose()
{
}

void Scenes::setScene(Scene* newScene)
{
	currentScene.reset(newScene);
}

Scene* Scenes::getCurrentScene()
{
	return currentScene.get();
}
