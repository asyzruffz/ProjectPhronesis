/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "game_object.hpp"

#include <memory>
using namespace std;

GameObject::GameObject(string name) : Entity(name)
{
}

void GameObject::start()
{
	// only run when enabled
	if (isEnabled() && mp_parent->isEnabled())
	{
		//Call the start method for each component in this game object
		for (map<type_index, Component::Ptr>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			it->second->start();
		}

		//Call the start method for each child of this game object
		for (vector<Entity::Ptr>::iterator it = getChildren().begin(); it != getChildren().end(); ++it)
		{
			static_pointer_cast<GameObject>(*it)->start();
		}
	}
}

void GameObject::update(float dt)
{
	// only run when enabled
	if (isEnabled() && mp_parent->isEnabled()) {
		//Call the update method for each component in this game object
		for (map<type_index, Component::Ptr>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			it->second->update(dt);
		}

		//Call the update method for each child of this game object
		for (vector<Entity::Ptr>::iterator it = getChildren().begin(); it != getChildren().end(); ++it)
		{
			static_pointer_cast<GameObject>(*it)->update(dt);
		}
	}
}

void GameObject::fixedUpdate(float dt)
{
	// only run when enabled
	if (isEnabled() && mp_parent->isEnabled()) {
		//Call the fixedUpdate method for each component in this game object
		for (map<type_index, Component::Ptr>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			it->second->fixedUpdate(dt);
		}

		//Call the fixedUpdate method for each child of this game object
		for (vector<Entity::Ptr>::iterator it = getChildren().begin(); it != getChildren().end(); ++it)
		{
			static_pointer_cast<GameObject>(*it)->fixedUpdate(dt);
		}
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// only run when enabled
	if (isEnabled() && mp_parent->isEnabled())
	{
		//Call the draw method for each component in this game object
		for (map<type_index, Component::Ptr>::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			it->second->draw(target, states);
		}

		//Call the draw method for each child of this game object
		for (vector<Entity::Ptr>::const_iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			static_pointer_cast<GameObject>(*it)->draw(target, states);
		}
	}
}
