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

	void onCollisionEnter2D(GameObject& other);
	void onCollisionExit2D(GameObject& other);

private:

	float m_movementSpeed;
	float m_turningSpeed;
	bool m_lastClicked;
};

#endif // PLAYER_CONTROLLER_HPP
