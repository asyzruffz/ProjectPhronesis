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
#include <memory>
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

enum class BodyShapeType
{
	Box,
	Circle,
	Polygon // unused
};

class Rigidbody2D : public Component
{
public:

	Rigidbody2D(const BodyType& bodyType = BodyType::Dynamic,
				const BodyShapeType& shapeType = BodyShapeType::Box);
	Rigidbody2D(const Rigidbody2D& original);

	virtual void awake();
	virtual void start();
	virtual void fixedUpdate(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static void setGravity(sf::Vector2f gravity);

	void startContact(GameObject& other);
	void endContact(GameObject& other);
	void addEnterCollisionEvent(CollisionEvent enterEvent);
	void addExitCollisionEvent(CollisionEvent exitEvent);

	// Settings that can be called before start
	void setIsTrigger(const bool& trigger);
	void setShape(const BodyShapeType& shapeType);

	void setDrawBody(const bool& enabled);
	bool isInContact() const;
	void addForce(const sf::Vector2f& force);
	void setLinearVelocity(const sf::Vector2f& velocity);
	void setAngularVelocity(const float& omega);
	sf::Vector2f getLinearVelocity();
	float getAngularVelocity();
	void setBullet(const bool& enabled);
	void setBodyTransform(const sf::Vector2f& position, const float& angle);
	void setRestitution(const float& value);

private:

	b2Body* mp_body;
	b2BodyDef m_bodyDef;
	unique_ptr<b2Shape> m_bodyShape;
	unique_ptr<sf::Shape> m_drawShape;
	BodyShapeType m_shapeType;
	b2FixtureDef m_bodyFixtureDef;
	BodyType m_bodyType;
	int m_numContacts;
	bool m_drawBody;

	vector<CollisionEvent> enterCollisionEvents;
	vector<CollisionEvent> exitCollisionEvents;

	virtual Rigidbody2D* doClone();

};

#endif // RIGIDBODY_2D_HPP
