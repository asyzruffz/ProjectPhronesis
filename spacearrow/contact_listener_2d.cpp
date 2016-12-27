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
	Rigidbody2D *rigidBodyA = nullptr, *rigidBodyB = nullptr;
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		rigidBodyA = static_cast<Rigidbody2D*>(bodyUserData);
	}
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		rigidBodyB = static_cast<Rigidbody2D*>(bodyUserData);
	}

	// Trigger callback for contact begin
	rigidBodyA->startContact(*rigidBodyB);
	rigidBodyB->startContact(*rigidBodyA);
}

void ContactListener2D::EndContact(b2Contact* contact)
{
	// Getting the entities contacted
	Rigidbody2D *rigidBodyA = nullptr, *rigidBodyB = nullptr;
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		rigidBodyA = static_cast<Rigidbody2D*>(bodyUserData);
	}
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
		rigidBodyB = static_cast<Rigidbody2D*>(bodyUserData);
	}

	// Trigger callback for contact end
	rigidBodyA->endContact(*rigidBodyB);
	rigidBodyB->endContact(*rigidBodyA);
}
