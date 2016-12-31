/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef GRAVITATIONAL_ATTRACTION_HPP
#define GRAVITATIONAL_ATTRACTION_HPP

#include <map>
using namespace std;

#include "script_component.hpp"

class GravitationalAttraction : public ScriptComponent
{
public:

	GravitationalAttraction(const float& gravity = 0.0f);

	void start();
	void fixedUpdate(float dt);

	void onCollisionEnter2D(GameObject& other);
	void onCollisionExit2D(GameObject& other);

	virtual GravitationalAttraction* doClone();

private:

	float m_gravity;
	map<int, GameObject*> m_attractedObjects;
};

#endif // GRAVITATIONAL_ATTRACTION_HPP