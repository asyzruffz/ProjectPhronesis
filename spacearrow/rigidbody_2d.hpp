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

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Rigidbody2D : public Component
{
public:

	Rigidbody2D(bool isDynamic = true);

	virtual void awake();
	virtual void start();
	virtual void fixedUpdate(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	static void setGravity(sf::Vector2f gravity);

	void addForce(const sf::Vector2f& force);
	bool IsInContact() const;

	void startContact(Rigidbody2D& other);
	void endContact(Rigidbody2D& other);

private:

	sf::RectangleShape m_rect;
	b2Body* mp_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_bodyShape;
	b2FixtureDef m_bodyFixtureDef;
	bool m_isDynamic;
	int m_numContacts;

};

#endif // RIGIDBODY_2D_HPP
