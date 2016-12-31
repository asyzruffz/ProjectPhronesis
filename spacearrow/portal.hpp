/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "script_component.hpp"

class Portal : public ScriptComponent
{
public:

	Portal(GameObject* otherSide);

	void start();
	void fixedUpdate(float dt);

	void onCollisionEnter2D(GameObject& other);
	void onCollisionExit2D(GameObject& other);

	virtual Portal* doClone();

private:

	GameObject* m_otherSide;
	sf::Vector2f m_exitPoint;
	float m_exitAngleShift;
	bool m_sending;
	GameObject* m_transferBody;

};

#endif // PORTAL_HPP