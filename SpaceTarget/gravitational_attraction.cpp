/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "gravitational_attraction.hpp"

#include <cmath>
using namespace std;

#include "transform_2d.hpp"
#include "rigidbody_2d.hpp"

GravitationalAttraction::GravitationalAttraction(const float& gravity)
{
	m_gravity = gravity;
}

void GravitationalAttraction::start()
{
	ScriptComponent::start();
}

void GravitationalAttraction::fixedUpdate(float dt)
{
	for (map<int, GameObject*>::iterator it = m_attractedObjects.begin(); it != m_attractedObjects.end(); ++it)
	{
		sf::Vector2f direction = getComponent<Transform2D>().getGlobalPosition() - it->second->getComponent<Transform2D>().getGlobalPosition();
		float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		direction /= magnitude;

		it->second->getComponent<Rigidbody2D>().addForce(direction * m_gravity);
	}
}

void GravitationalAttraction::onCollisionEnter2D(GameObject& other)
{
	m_attractedObjects[other.getId()] = &other;
}

void GravitationalAttraction::onCollisionExit2D(GameObject& other)
{
	m_attractedObjects.erase(other.getId());
}

void GravitationalAttraction::stopAttracting(int entityId)
{
	if (m_attractedObjects.count(entityId) > 0)
	{
		m_attractedObjects.erase(entityId);
	}
}

GravitationalAttraction* GravitationalAttraction::doClone()
{
	return new GravitationalAttraction(*this);
}
