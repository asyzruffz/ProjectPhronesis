/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef TRANSFORM_2D_HPP
#define TRANSFORM_2D_HPP

#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "component.hpp"

class Transform2D : public Component, public sf::Transformable
{
public:

	Transform2D();

	sf::Vector2f getGlobalPosition();
	float getGlobalRotation();
	sf::Vector2f getGlobalScale();
	sf::Transform getGlobalTransform();

	void setGlobalPosition(const sf::Vector2f& position);
	void setGlobalPosition(const float& posX, const float& posY);
	void setGlobalRotation(const float& rotation);
	void setGlobalScale(const sf::Vector2f& scale);

	sf::Vector2f up();
	sf::Vector2f right();

	Entity::Ptr getParent();

	virtual Transform2D* doClone();

};

#endif // TRANSFORM_2D_HPP
