#pragma once

#include "Entity.hpp"
#include "Component.hpp"

namespace Phronesis
{
	template<typename T>
	bool Component::has() const noexcept
	{
		if(auto entity = owner.lock())
		{
			return entity->has<T>();
		}
		return false;
	}

	template<typename T>
	T& Component::get()
	{
		auto entity = owner.lock();
		return entity->get<T>();
	}
}
