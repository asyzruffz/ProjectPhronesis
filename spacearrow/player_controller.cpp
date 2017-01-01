/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "player_controller.hpp"

#include <cmath>
using namespace std;

#include "transform_2d.hpp"
#include "rigidbody_2d.hpp"
#include "object_spawner.hpp"

void PlayerController::start()
{
	m_movementSpeed = 500;
	m_turningSpeed = 100;
	m_lastPressed = false;
	m_lastClicked = false;
	m_mouseDraggedUp = false;
}

void PlayerController::update(float dt)
{
	dragMouse();
	if (m_mouseDraggedUp)
	{
		m_mouseDraggedUp = false;
		shoot(m_dragDistance);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_lastPressed)
	{
		shoot(30.0f);
	}

	m_lastPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void PlayerController::fixedUpdate(float dt)
{
	Transform2D& transform = getComponent<Transform2D>();
	Rigidbody2D& rigidbody = getComponent<Rigidbody2D>();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rigidbody.setAngularVelocity(m_turningSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rigidbody.setAngularVelocity(-m_turningSpeed * dt);
	}
	else
	{
		rigidbody.setAngularVelocity(0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		rigidbody.addForce(transform.up() * m_movementSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		rigidbody.addForce(transform.up() * m_movementSpeed * -1.0f * dt);
	}
}

void PlayerController::dragMouse()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_lastClicked)
	{
		// Start dragging
		m_mouseStartPos = sf::Mouse::getPosition();
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_lastClicked)
	{
		// End dragging
		m_mouseDraggedUp = true;
		sf::Vector2i mousePosDelta = sf::Mouse::getPosition() - m_mouseStartPos;
		m_dragDistance = (float)sqrt(pow(mousePosDelta.x, 2) + pow(mousePosDelta.y, 2));
	}

	m_lastClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void PlayerController::shoot(float speed)
{
	Transform2D& transform = getComponent<Transform2D>();

	Entity::Ptr bullet = getComponent<ObjectSpawner>().spawn(transform.getGlobalPosition() + transform.up() * 2.0f, transform.getGlobalRotation());
	bullet->getComponent<Rigidbody2D>().setLinearVelocity(transform.up() * speed);
}
