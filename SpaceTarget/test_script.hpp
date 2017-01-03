/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef TEST_SCRIPT_HPP
#define TEST_SCRIPT_HPP

#include "script_component.hpp"

class TestScript : public ScriptComponent
{
public:

	void start();

	void onCollisionEnter2D(GameObject& other);
	void onCollisionExit2D(GameObject& other);

	virtual TestScript* doClone();

};

#endif // TEST_SCRIPT_HPP