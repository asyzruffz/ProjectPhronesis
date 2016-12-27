/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "rigidbody_2d.hpp"

#include <iostream>
using namespace std;

#include "scene.hpp"
#include "component.ext.hpp"
#include "transform_2d.hpp"
#include "sprite.hpp"

Rigidbody2D::Rigidbody2D(bool isDynamic)
{
	m_isDynamic = isDynamic;
	m_numContacts = 0;
}

void Rigidbody2D::awake()
{
	// Set a rectangle (to be drawn in case no sprite attached)
	sf::Vector2f rectSize(Sprite::PIXEL_PER_METER, Sprite::PIXEL_PER_METER);
	m_rect = sf::RectangleShape(rectSize);
	m_rect.setOrigin(rectSize / 2.0f);
	m_rect.setFillColor(sf::Color::White);
	m_rect.setOutlineThickness(1);
	m_rect.setOutlineColor(sf::Color::Black);

	// Set whether dynamic
	if (m_isDynamic)
	{
		m_bodyDef.type = b2_dynamicBody;
	}
	else
	{
		m_bodyDef.type = b2_staticBody;
	}
}

void Rigidbody2D::start()
{
	Transform2D& trans = getComponent<Transform2D>();

	// Set starting position
	m_bodyDef.position = b2Vec2(trans.getPosition().x, trans.getPosition().y);
	m_bodyDef.angle = trans.getGlobalRotation() * b2_pi / 180;
	m_rect.setPosition(trans.getGlobalPosition());
	m_rect.setRotation(trans.getGlobalRotation());
	m_rect.setSize(trans.getGlobalScale() * Sprite::PIXEL_PER_METER);
	m_rect.setOrigin(trans.getGlobalScale() * Sprite::PIXEL_PER_METER / 2.0f);

	// Set shape as box
	if (hasComponent<Sprite>())
	{
		Sprite& sprite = getComponent<Sprite>();
		sf::Vector2f spriteSize = sprite.getSpriteSize();

		// The body size is of sprite size multiplied with the scale
		m_bodyShape.SetAsBox(spriteSize.x * trans.getGlobalScale().x / Sprite::PIXEL_PER_METER * 0.5f, // param need half
							spriteSize.y * trans.getGlobalScale().y / Sprite::PIXEL_PER_METER * 0.5f); // width/height
	}
	else
	{
		// The body size of rectangle is (1, 1) multiplied with the scale
		m_bodyShape.SetAsBox(trans.getGlobalScale().x * 0.5f, trans.getGlobalScale().y * 0.5f); // param need half width/height
	}

	m_bodyFixtureDef.shape = &m_bodyShape;
	m_bodyFixtureDef.density = 0.3f;
	m_bodyFixtureDef.friction = 0.5f;

	mp_body = Scene::world.CreateBody(&m_bodyDef);
	mp_body->CreateFixture(&m_bodyFixtureDef);
	mp_body->SetUserData(mp_owner);
}

void Rigidbody2D::fixedUpdate(float dt)
{
	// Update the transform of the body to the Transform2D component
	Transform2D& trans = getComponent<Transform2D>();

	trans.setGlobalPosition(mp_body->GetPosition().x, mp_body->GetPosition().y);
	// Box2D uses radians for rotation, SFML uses degree
	trans.setGlobalRotation(mp_body->GetAngle() * 180 / b2_pi);

	if (!hasComponent<Sprite>())
	{
		m_rect.setPosition(trans.getGlobalPosition() * Sprite::PIXEL_PER_METER);
		m_rect.setRotation(trans.getGlobalRotation());
		m_rect.setSize(trans.getGlobalScale() * Sprite::PIXEL_PER_METER);
		m_rect.setOrigin(trans.getGlobalScale() * Sprite::PIXEL_PER_METER / 2.0f);
	}
}

void Rigidbody2D::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw rect if no sprite attached
	if (!hasComponent<Sprite>())
	{
		target.draw(m_rect, states);
	}
}

void Rigidbody2D::setGravity(sf::Vector2f gravity)
{
	Scene::world.SetGravity(b2Vec2(gravity.x, gravity.y));
}

void Rigidbody2D::addForce(const sf::Vector2f & force)
{
	b2Vec2 forceVector = mp_body->GetWorldVector(b2Vec2(force.x, force.y));
	b2Vec2 pointToApplyForce = mp_body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
	mp_body->ApplyForce(forceVector, pointToApplyForce);
}

bool Rigidbody2D::IsInContact() const
{
	return m_numContacts > 0;
}

void Rigidbody2D::startContact(Rigidbody2D& other)
{
	m_numContacts++;
	cout << "Rigidbody2D: " << mp_owner->getName() << " start colliding with " << other.mp_owner->getName() << endl;
}

void Rigidbody2D::endContact(Rigidbody2D& other)
{
	m_numContacts--;
	cout << "Rigidbody2D: " << mp_owner->getName() << " stop colliding with " << other.mp_owner->getName() << endl;
}
