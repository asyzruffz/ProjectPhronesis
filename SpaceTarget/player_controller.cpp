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

#include "game_data.hpp"
#include "transform_2d.hpp"
#include "rigidbody_2d.hpp"
#include "sprite.hpp"
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
	// Get mouse position relative to world
	m_mousePos = GameData::instance().window->mapPixelToCoords(sf::Mouse::getPosition(*GameData::instance().window)) / Sprite::PIXEL_PER_METER;

	Transform2D& transform = getComponent<Transform2D>();
	sf::Vector2f deltaPos = m_mousePos - transform.getGlobalPosition();
	float angle = atan2f(deltaPos.x, -deltaPos.y) * RAD_TO_DEG;

	// Rotate player based on mouse position
	transform.setRotation(angle);

	dragMouse();
	if (m_mouseDraggedUp)
	{
		// Shoot with bullet speed from drag distance (min speed 2)
		shoot(max(m_dragDistance, 2.0f));
		m_mouseDraggedUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_lastPressed)
	{
		shoot(30.0f);
	}

	m_lastPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void PlayerController::fixedUpdate(float dt)
{
	
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
	bullet->getComponent<Rigidbody2D>().setBullet(true);
}
