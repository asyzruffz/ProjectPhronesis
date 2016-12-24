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

GameObject::GameObject()
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

void GameObject::draw(sf::RenderWindow & window)
{
	// only run when enabled
	if (isEnabled() && mp_parent->isEnabled())
	{
		//Call the draw method for each component in this game object
		for (map<type_index, Component::Ptr>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			it->second->draw(window);
		}

		//Call the draw method for each child of this game object
		for (vector<Entity::Ptr>::iterator it = getChildren().begin(); it != getChildren().end(); ++it)
		{
			static_pointer_cast<GameObject>(*it)->draw(window);
		}
	}
}
