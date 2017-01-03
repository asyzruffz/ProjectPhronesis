/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "camera_2d.hpp"

#include "game_data.hpp"
#include "game_object.hpp"
#include "component.ext.hpp"
#include "transform_2d.hpp"
#include "sprite.hpp"

Camera2D::Camera2D()
{
	m_target = nullptr;
}

void Camera2D::start()
{
	Transform2D& trans = getComponent<Transform2D>();

	m_view = GameData::instance().window->getView();
	m_view.zoom(trans.getGlobalScale().y);

	GameData::instance().window->setView(m_view);
}

void Camera2D::update(float dt)
{
	Transform2D& trans = getComponent<Transform2D>();

	// Camera follows a target (if any)
	if (m_target)
	{
		sf::Vector2f targetPosition = m_target->getComponent<Transform2D>().getGlobalPosition();
		trans.setPosition(trans.getPosition() + (targetPosition - trans.getPosition()) * dt);
	}

	m_view = GameData::instance().window->getView();

	m_view.setCenter(trans.getGlobalPosition() * Sprite::PIXEL_PER_METER);
	m_view.setRotation(trans.getGlobalRotation());
	
	GameData::instance().window->setView(m_view);
}

void Camera2D::setTarget(GameObject* target)
{
	m_target = target;
}

Camera2D* Camera2D::doClone()
{
	return new Camera2D(*this);
}
