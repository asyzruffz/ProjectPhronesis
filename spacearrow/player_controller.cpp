/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "player_controller.hpp"

#include "transform_2d.hpp"
#include "rigidbody_2d.hpp"
#include "object_spawner.hpp"

void PlayerController::start()
{
	ScriptComponent::start();

	m_movementSpeed = 10;
	m_turningSpeed = 3;
	m_lastClicked = false;
}

void PlayerController::update(float dt)
{
	Transform2D& transform = getComponent<Transform2D>();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_lastClicked)
	{
		getComponent<ObjectSpawner>().spawn(transform.getGlobalPosition() + transform.up() * 5.0f, transform.getGlobalRotation());
	}

	m_lastClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void PlayerController::fixedUpdate(float dt)
{
	Transform2D& transform = getComponent<Transform2D>();
	Rigidbody2D& rigidbody = getComponent<Rigidbody2D>();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rigidbody.SetAngularVelocity(m_turningSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rigidbody.SetAngularVelocity(-m_turningSpeed);
	}
	else
	{
		rigidbody.SetAngularVelocity(0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		rigidbody.addForce(transform.up() * m_movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		rigidbody.addForce(transform.up() * m_movementSpeed * -1.0f);
	}
}

void PlayerController::onCollisionEnter2D(GameObject & other)
{
}

void PlayerController::onCollisionExit2D(GameObject & other)
{
}
