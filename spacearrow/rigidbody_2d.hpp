/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef RIGIDBODY_2D_HPP
#define RIGIDBODY_2D_HPP

#include "component.hpp"
#include "game_object.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <vector>
#include <functional>
using namespace std;

#define DEG_TO_RAD 0.0174532925199432957f
#define RAD_TO_DEG 57.295779513082320876f

// Function pointer to represent the event of collisions
typedef function<void(GameObject&)> CollisionEvent;

enum class BodyType
{
	Static,
	Dynamic,
	Kinematic
};

class Rigidbody2D : public Component
{
public:

	Rigidbody2D(BodyType bodyType = BodyType::Dynamic);

	virtual void awake();
	virtual void start();
	virtual void fixedUpdate(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static void setGravity(sf::Vector2f gravity);

	void addForce(const sf::Vector2f& force);
	bool IsInContact() const;

	void startContact(GameObject& other);
	void endContact(GameObject& other);
	void addEnterCollisionEvent(CollisionEvent enterEvent);
	void addExitCollisionEvent(CollisionEvent exitEvent);

private:

	sf::RectangleShape m_rect;
	b2Body* mp_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_bodyShape;
	b2FixtureDef m_bodyFixtureDef;
	BodyType m_bodyType;
	int m_numContacts;

	vector<CollisionEvent> enterCollisionEvents;
	vector<CollisionEvent> exitCollisionEvents;

};

#endif // RIGIDBODY_2D_HPP
