/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "portal.hpp"

#include <cmath>
using namespace std;

#include "transform_2d.hpp"
#include "rigidbody_2d.hpp"

Portal::Portal(GameObject* otherSide)
{
	m_otherSide = otherSide;
	m_sending = false;
}

void Portal::start()
{
	ScriptComponent::start();

	if (m_otherSide)
	{
		m_exitPoint = m_otherSide->getComponent<Transform2D>().getGlobalPosition();
		m_exitAngleShift = m_otherSide->getComponent<Transform2D>().getGlobalRotation() - getComponent<Transform2D>().getGlobalRotation();
	}
}

void Portal::fixedUpdate(float dt)
{
	if (m_sending && m_transferBody->hasComponent<Rigidbody2D>())
	{
		Rigidbody2D& rigidbody = m_transferBody->getComponent<Rigidbody2D>();
		sf::Vector2f enterVelocity = rigidbody.getLinearVelocity();
		float enterAngle = m_transferBody->getComponent<Transform2D>().getGlobalRotation();
		
		float speed = sqrt(pow(enterVelocity.x, 2) + pow(enterVelocity.y, 2));
		sf::Vector2f offset = enterVelocity / speed * 3.0f;

		// Transform to rotate the velocity
		sf::Transform rotateTransform = sf::Transform::Identity;
		rotateTransform.rotate(m_exitAngleShift);

		// Set the body to go out another portal
		rigidbody.setBodyTransform(m_exitPoint + (rotateTransform * offset),
									enterAngle + m_exitAngleShift);
		rigidbody.setLinearVelocity(rotateTransform * enterVelocity);
		m_sending = false;
	}
}

void Portal::onCollisionEnter2D(GameObject& other)
{
	m_transferBody = &other;
	m_sending = true;
}

void Portal::onCollisionExit2D(GameObject& other)
{
	
}

Portal* Portal::doClone()
{
	return new Portal(*this);
}
