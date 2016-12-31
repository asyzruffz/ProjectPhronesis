/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "rigidbody_2d.hpp"

#include "scene.hpp"
#include "component.ext.hpp"
#include "transform_2d.hpp"
#include "sprite.hpp"

Rigidbody2D::Rigidbody2D(const BodyType& bodyType, const BodyShapeType& shapeType)
{
	m_bodyType = bodyType;
	m_shapeType = shapeType;
	m_numContacts = 0;
	m_drawBody = false;
}

Rigidbody2D::Rigidbody2D(const Rigidbody2D& original)
{
	m_bodyDef = original.m_bodyDef;
	m_shapeType = original.m_shapeType;
	m_bodyFixtureDef = original.m_bodyFixtureDef;
	m_bodyType = original.m_bodyType;
	m_numContacts = 0;
	m_drawBody = original.m_drawBody;

	enterCollisionEvents.clear();
	exitCollisionEvents.clear();
}

void Rigidbody2D::awake()
{
	// Set body type
	switch(m_bodyType)
	{
		default:
		case BodyType::Static:
			m_bodyDef.type = b2_staticBody;
			break;
		case BodyType::Dynamic:
			m_bodyDef.type = b2_dynamicBody;
			break;
		case BodyType::Kinematic:
			m_bodyDef.type = b2_kinematicBody;
			break;
	}
}

void Rigidbody2D::start()
{
	Transform2D& trans = getComponent<Transform2D>();
	float radius;

	// Set shape
	if (hasComponent<Sprite>())
	{
		Sprite& sprite = getComponent<Sprite>();
		sf::Vector2f spriteSize = sprite.getSpriteSize();

		switch (m_shapeType)
		{
			default:
			case BodyShapeType::Box:
				m_bodyShape = unique_ptr<b2PolygonShape>(new b2PolygonShape());

				// The body size is of sprite size multiplied with the scale
				static_cast<b2PolygonShape*>(m_bodyShape.get())->SetAsBox(
					spriteSize.x * trans.getGlobalScale().x / Sprite::PIXEL_PER_METER * 0.5f,	// param need half
					spriteSize.y * trans.getGlobalScale().y / Sprite::PIXEL_PER_METER * 0.5f	// width/height
					);
				break;

			case BodyShapeType::Circle:
				m_bodyShape = unique_ptr<b2CircleShape>(new b2CircleShape());

				// The body size is of max sprite size multiplied with the scale
				radius = (spriteSize.x * trans.getGlobalScale().x) > (spriteSize.y * trans.getGlobalScale().y)
					? spriteSize.x * trans.getGlobalScale().x / Sprite::PIXEL_PER_METER * 0.5f
					: spriteSize.y * trans.getGlobalScale().y / Sprite::PIXEL_PER_METER * 0.5f;
				static_cast<b2CircleShape*>(m_bodyShape.get())->m_radius = radius;
				break;
		}
	}
	else
	{
		// (in case no sprite attached)
		switch (m_shapeType)
		{
			default:
			case BodyShapeType::Box:
				// Set a rectangle to be drawn
				m_drawShape = unique_ptr<sf::RectangleShape>(new sf::RectangleShape(trans.getGlobalScale() * Sprite::PIXEL_PER_METER));

				m_bodyShape = unique_ptr<b2PolygonShape>(new b2PolygonShape());
				// The body size of rectangle is (1, 1) multiplied with the scale
				static_cast<b2PolygonShape*>(m_bodyShape.get())->SetAsBox(trans.getGlobalScale().x * 0.5f, trans.getGlobalScale().y * 0.5f); // param need half width/height
				break;
			case BodyShapeType::Circle:
				// The body size of circle with diameter 1 multiplied with the scale
				radius = trans.getGlobalScale().x > trans.getGlobalScale().y ? trans.getGlobalScale().x * 0.5f : trans.getGlobalScale().y * 0.5f;

				// Set a circle to be drawn
				m_drawShape = unique_ptr<sf::CircleShape>(new sf::CircleShape(radius * Sprite::PIXEL_PER_METER));

				m_bodyShape = unique_ptr<b2CircleShape>(new b2CircleShape());
				static_cast<b2CircleShape*>(m_bodyShape.get())->m_radius = radius;
				break;
		}

		m_drawShape->setFillColor(sf::Color::White);
		m_drawShape->setOutlineThickness(1);
		m_drawShape->setOutlineColor(sf::Color::Black);
	}

	// Set starting position
	m_bodyDef.position = b2Vec2(trans.getGlobalPosition().x, trans.getGlobalPosition().y);
	m_bodyDef.angle = trans.getGlobalRotation() * DEG_TO_RAD;
	if (!hasComponent<Sprite>())
	{
		m_drawShape->setOrigin(trans.getGlobalScale() * Sprite::PIXEL_PER_METER / 2.0f);
		m_drawShape->setPosition(trans.getGlobalPosition());
		m_drawShape->setRotation(trans.getGlobalRotation());
	}

	m_bodyFixtureDef.shape = m_bodyShape.get();
	m_bodyFixtureDef.density = 0.3f;
	m_bodyFixtureDef.friction = 0.5f;

	mp_body = Scene::world.CreateBody(&m_bodyDef);
	mp_body->CreateFixture(&m_bodyFixtureDef);
	mp_body->SetUserData(&getGameObject());
}

void Rigidbody2D::fixedUpdate(float dt)
{
	// Update the transform of the body to the Transform2D component
	Transform2D& trans = getComponent<Transform2D>();

	if (m_bodyType == BodyType::Dynamic)
	{
		// Dynamic body updates the transform
		trans.setGlobalPosition(mp_body->GetPosition().x, mp_body->GetPosition().y);
		trans.setGlobalRotation(mp_body->GetAngle() * RAD_TO_DEG); // Box2D uses radians for rotation, SFML uses degree
	}
	else
	{
		// Transform updates the static/kinematic body
		mp_body->SetTransform(b2Vec2(trans.getGlobalPosition().x, trans.getGlobalPosition().y),
								trans.getGlobalRotation() * DEG_TO_RAD);
	}

	// No sprite, update the rectangle
	if (!hasComponent<Sprite>())
	{
		m_drawShape->setPosition(trans.getGlobalPosition() * Sprite::PIXEL_PER_METER);
		m_drawShape->setRotation(trans.getGlobalRotation());
		float radius;
		switch (m_shapeType)
		{
			default:
			case BodyShapeType::Box:
				static_cast<sf::RectangleShape*>(m_drawShape.get())->setSize(trans.getGlobalScale() * Sprite::PIXEL_PER_METER);
				break;
			case BodyShapeType::Circle:
				radius = trans.getGlobalScale().x > trans.getGlobalScale().y ? trans.getGlobalScale().x * 0.5f : trans.getGlobalScale().y * 0.5f;
				static_cast<sf::CircleShape*>(m_drawShape.get())->setRadius(radius * Sprite::PIXEL_PER_METER);
				break;
		}
	}
}

void Rigidbody2D::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw rect if no sprite attached
	if (!hasComponent<Sprite>() && m_drawBody)
	{
		target.draw(*m_drawShape, states);
	}
}

void Rigidbody2D::setGravity(sf::Vector2f gravity)
{
	Scene::world.SetGravity(b2Vec2(gravity.x, gravity.y));
}

void Rigidbody2D::startContact(GameObject& other)
{
	m_numContacts++;

	// Call the event callback when starting collision
	for (vector<CollisionEvent>::size_type i = 0; i < enterCollisionEvents.size(); i++)
	{
		enterCollisionEvents[i](other);
	}
}

void Rigidbody2D::endContact(GameObject& other)
{
	m_numContacts--;

	// Call the event callback when ending collision
	for (vector<CollisionEvent>::size_type i = 0; i < exitCollisionEvents.size(); i++)
	{
		exitCollisionEvents[i](other);
	}
}

void Rigidbody2D::addEnterCollisionEvent(CollisionEvent enterEvent)
{
	enterCollisionEvents.push_back(enterEvent);
}

void Rigidbody2D::addExitCollisionEvent(CollisionEvent exitEvent)
{
	exitCollisionEvents.push_back(exitEvent);
}

void Rigidbody2D::setIsTrigger(const bool& trigger)
{
	m_bodyFixtureDef.isSensor = trigger;
}

void Rigidbody2D::setShape(const BodyShapeType& shapeType)
{
	m_shapeType = shapeType;
}

void Rigidbody2D::setDrawBody(const bool& enabled)
{
	m_drawBody = enabled;
}

bool Rigidbody2D::isInContact() const
{
	return m_numContacts > 0;
}

void Rigidbody2D::addForce(const sf::Vector2f& force)
{
	b2Vec2 pointToApplyForce = mp_body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
	mp_body->ApplyForce(b2Vec2(force.x, force.y), pointToApplyForce, true);
}

void Rigidbody2D::setLinearVelocity(const sf::Vector2f& velocity)
{
	mp_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

void Rigidbody2D::setAngularVelocity(const float& omega)
{
	mp_body->SetAngularVelocity(omega);
}

sf::Vector2f Rigidbody2D::getLinearVelocity()
{
	return sf::Vector2f(mp_body->GetLinearVelocity().x, mp_body->GetLinearVelocity().y);
}

float Rigidbody2D::getAngularVelocity()
{
	return mp_body->GetAngularVelocity();
}

void Rigidbody2D::setBodyTransform(const sf::Vector2f& position, const float& angle)
{
	mp_body->SetTransform(b2Vec2(position.x, position.y), angle * DEG_TO_RAD);
}

Rigidbody2D* Rigidbody2D::doClone()
{
	return new Rigidbody2D(*this);
}
