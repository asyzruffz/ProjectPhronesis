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

sf::Vector2f Transform2D::getGlobalPosition()
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		// Get parent's position & rotation
		Transform2D& parentTransform2D = getParent()->getComponent<Transform2D>();
		sf::Vector2f parentPosition = parentTransform2D.getGlobalPosition();
		float parentRotation = parentTransform2D.getGlobalRotation();
		
		// Make a transform to rotate position based on parent's rotation
		sf::Transform rotateTransform = sf::Transform::Identity;
		rotateTransform.rotate(parentRotation);

		return parentPosition + rotateTransform.transformPoint(getPosition());
	}
	else
	{
		return getPosition();
	}
}

float Transform2D::getGlobalRotation()
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		float parentRotation = getParent()->getComponent<Transform2D>().getGlobalRotation();
		return parentRotation + getRotation();
	}
	else
	{
		return getRotation();
	}
}

sf::Vector2f Transform2D::getGlobalScale()
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		sf::Vector2f parentScale = getParent()->getComponent<Transform2D>().getGlobalScale();
		return sf::Vector2f(parentScale.x * getScale().x, parentScale.y * getScale().y);
	}
	else
	{
		return getScale();
	}
}

sf::Transform Transform2D::getGlobalTransform()
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		sf::Transform parentTransform = getParent()->getComponent<Transform2D>().getGlobalTransform();
		return parentTransform * getTransform();
	}
	else
	{
		return getTransform();
	}
}

void Transform2D::setGlobalPosition(const sf::Vector2f& position)
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		sf::Vector2f parentPosition = getParent()->getComponent<Transform2D>().getGlobalPosition();
		setPosition(position - parentPosition);
	}
	else
	{
		setPosition(position);
	}
}

void Transform2D::setGlobalPosition(const float & posX, const float & posY)
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		sf::Vector2f parentPosition = getParent()->getComponent<Transform2D>().getGlobalPosition();
		setPosition(posX - parentPosition.x, posY - parentPosition.y);
	}
	else
	{
		setPosition(posX, posY);
	}
}

void Transform2D::setGlobalRotation(const float& rotation)
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		float parentRotation = getParent()->getComponent<Transform2D>().getGlobalRotation();
		setRotation(rotation - parentRotation);
	}
	else
	{
		setRotation(rotation);
	}
}

void Transform2D::setGlobalScale(const sf::Vector2f& scale)
{
	if (getParent() && getParent()->hasComponent<Transform2D>())
	{
		sf::Vector2f parentScale = getParent()->getComponent<Transform2D>().getGlobalScale();
		setScale(scale - parentScale);
	}
	else
	{
		setScale(scale);
	}
}

sf::Vector2f Transform2D::up()
{
	sf::Vector2f upDirection(0, -1);

	// Make a transform to rotate position based on rotation
	sf::Transform rotateTransform = sf::Transform::Identity;
	rotateTransform.rotate(getGlobalRotation());

	return rotateTransform.transformPoint(upDirection);
}

sf::Vector2f Transform2D::right()
{
	sf::Vector2f rightDirection(1, 0);

	// Make a transform to rotate position based on rotation
	sf::Transform rotateTransform = sf::Transform::Identity;
	rotateTransform.rotate(getGlobalRotation());

	return rotateTransform.transformPoint(rightDirection);
}

Entity::Ptr Transform2D::getParent()
{
	return getGameObject().getParent();
}

Transform2D* Transform2D::doClone()
{
	return new Transform2D(*this);
}
