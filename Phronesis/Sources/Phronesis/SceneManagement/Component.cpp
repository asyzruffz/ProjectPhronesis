#include "StdAfx.hpp"
#include "Component.hpp"

using namespace Phronesis;

Component::Component()
{
}

void Component::start()
{
}

void Component::update()
{
}

Entity& Component::getGameObject() const
{
	return *owner.lock();
}
