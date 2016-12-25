/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "transform_2d.hpp"

Transform2D::Transform2D()
{
	setPosition(0, 0);
	setRotation(0);
	setScale(1, 1);
}

/*sf::Vector2f Transform2D::getLocalPosition()
{
	return m_position;
}

float Transform2D::getLocalRotation()
{
	return m_rotation;
}

sf::Vector2f Transform2D::getLocalScale()
{
	return m_scale;
}*/

sf::Vector2f Transform2D::getGlobalPosition()
{
	if (getParent()->getName() == "Root")
	{
		return getPosition();
	}
	else
	{
		sf::Vector2f parentPosition = getParent()->getComponent<Transform2D>().getGlobalPosition();
		return parentPosition + getPosition();
	}
}

float Transform2D::getGlobalRotation()
{
	if (getParent()->getName() == "Root")
	{
		return getRotation();
	}
	else
	{
		float parentRotation = getParent()->getComponent<Transform2D>().getGlobalRotation();
		return parentRotation + getRotation();
	}
}

sf::Vector2f Transform2D::getGlobalScale()
{
	if (getParent()->getName() == "Root")
	{
		return getScale();
	}
	else
	{
		sf::Vector2f parentScale = getParent()->getComponent<Transform2D>().getGlobalScale();
		return sf::Vector2f(parentScale.x * getScale().x, parentScale.y * getScale().y);
	}
}

sf::Transform Transform2D::getGlobalTransform()
{
	if (getParent()->getName() == "Root")
	{
		return getTransform();
	}
	else
	{
		sf::Transform parentTransform = getParent()->getComponent<Transform2D>().getGlobalTransform();
		return parentTransform * getTransform();
	}
}

Entity::Ptr Transform2D::getParent()
{
	return m_owner->getParent();
}
