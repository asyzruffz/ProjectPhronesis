
#include "StdAfx.hpp"
#include "Module.hpp"

#include "Engine.hpp"
#include "Game.hpp"

#include "Phronesis/Graphics/Window.hpp"
#include "Phronesis/Graphics/Renderer.hpp"

using namespace Phronesis;

template<typename T>
bool Module::hasModule()
{
	return Engine::Get()->getGame().hasModule<T>();
}

template<typename T>
T* Module::getModule()
{ 
	return Engine::Get()->getGame().getModule<T>(); 
}

void validateModuleHelpers()
{
	Module::hasModule<Window>();
	Module::getModule<Window>();

	Module::hasModule<Renderer>();
	Module::getModule<Renderer>();
}