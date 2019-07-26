#pragma once

#include "Module.hpp"
#include "Engine.hpp"
#include "Game.hpp"

namespace Phronesis
{
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
}
