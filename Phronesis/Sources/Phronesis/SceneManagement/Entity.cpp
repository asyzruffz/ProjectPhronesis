#include "StdAfx.hpp"
#include "Entity.hpp"

using namespace Phronesis;

Entity::Entity(const char* name) :
	name(name),
	enabled(true)
{
}

Entity::~Entity()
{
	components.clear();
	children.clear();
}

Entity::Ptr Entity::setParent(const Entity::Ptr& newParent)
{
	Entity::Ptr self;
	try { self = shared_from_this(); }
	catch(std::bad_weak_ptr&) { self = Entity::Ptr(this); }

	newParent->getChildren().push_back(self);
	parent = newParent;
	return self;
}

Entity::Ptr Entity::getParent() const
{
	return parent.lock();
}

std::vector<Entity::Ptr>& Entity::getChildren()
{
	return children;
}

void Entity::setEnabled(bool isEnabled)
{
	enabled = isEnabled;
}

bool Entity::isEnabled() const
{
	return (parent.expired() || getParent()->isEnabled()) && enabled;
}

std::string Entity::getName() const
{
	return name;
}

void Entity::start()
{
	// only run when enabled
	if(isEnabled())
	{
		// call the start method for each component in this game object
		for(auto it = components.begin(); it != components.end(); ++it)
		{
			it->second->start();
		}

		// call the start method for each child of this game object
		for(auto it = children.begin(); it != children.end(); ++it)
		{
			(*it)->start();
		}
	}
}

void Entity::update()
{
	// only run when enabled
	if(isEnabled())
	{
		// call the update method for each component in this game object
		for(auto it = components.begin(); it != components.end(); ++it)
		{
			it->second->update();
		}

		// call the update method for each child of this game object
		for(auto it = children.begin(); it != children.end(); ++it)
		{
			(*it)->update();
		}
	}
}
