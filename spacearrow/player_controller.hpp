/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "script_component.hpp"

class PlayerController : public ScriptComponent
{
public:

	void start();
	void update(float dt);
	void fixedUpdate(float dt);

private:

	float m_movementSpeed;
	float m_turningSpeed;
	bool m_lastPressed;
	bool m_lastClicked;
	bool m_mouseDraggedUp;
	sf::Vector2i m_mouseStartPos;
	float m_dragDistance;

	void dragMouse();
	void shoot(float speed);

};

#endif // PLAYER_CONTROLLER_HPP
