/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "contact_listener_2d.hpp"

#include "game_object.hpp"
#include "rigidbody_2d.hpp"

void ContactListener2D::BeginContact(b2Contact* contact)
{
	// Getting the entities contacted
	GameObject *p_entityA = nullptr, *p_entityB = nullptr;
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		p_entityA = static_cast<GameObject*>(bodyUserData);
	}
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		p_entityB = static_cast<GameObject*>(bodyUserData);
	}

	// Trigger callback for contact begin
	if (p_entityA->hasComponent<Rigidbody2D>() && p_entityB->hasComponent<Rigidbody2D>())
	{
		Rigidbody2D& rigidBodyA = p_entityA->getComponent<Rigidbody2D>();
		Rigidbody2D& rigidBodyB = p_entityB->getComponent<Rigidbody2D>();
		rigidBodyA.startContact(*p_entityB);
		rigidBodyB.startContact(*p_entityA);
	}
}

void ContactListener2D::EndContact(b2Contact* contact)
{
	// Getting the entities contacted
	GameObject *p_entityA = nullptr, *p_entityB = nullptr;
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		p_entityA = static_cast<GameObject*>(bodyUserData);
	}
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		p_entityB = static_cast<GameObject*>(bodyUserData);
	}

	// Trigger callback for contact end
	if (p_entityA->hasComponent<Rigidbody2D>() && p_entityB->hasComponent<Rigidbody2D>())
	{
		Rigidbody2D& rigidBodyA = p_entityA->getComponent<Rigidbody2D>();
		Rigidbody2D& rigidBodyB = p_entityB->getComponent<Rigidbody2D>();
		rigidBodyA.endContact(*p_entityB);
		rigidBodyB.endContact(*p_entityA);
	}
}
