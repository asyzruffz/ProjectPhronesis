/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef CAMERA_2D_HPP
#define CAMERA_2D_HPP

#include <SFML/Graphics.hpp>

#include "component.hpp"

class GameObject; // Forward declaration

class Camera2D : public Component
{
public:
	
	Camera2D();

	virtual void start();
	virtual void update(float dt);

	void setTarget(GameObject* target);

private:

	sf::View m_view;
	GameObject* m_target;

	virtual Camera2D* doClone();

};

#endif // CAMERA_2D_HPP
