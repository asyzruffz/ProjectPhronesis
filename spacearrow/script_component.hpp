/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include "component.hpp"

class Contact2D;

class ScriptComponent : public Component
{
public:

	ScriptComponent();

	void onCollisionEnter2D(Contact2D* other);
	void onCollisionExit2D(Contact2D* other);

};

#endif // SCRIPT_COMPONENT_HPP