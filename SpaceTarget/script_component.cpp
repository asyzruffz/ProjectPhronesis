/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "script_component.hpp"

#include <functional>
using namespace std;

#include "rigidbody_2d.hpp"

void ScriptComponent::start()
{
	if (hasComponent<Rigidbody2D>())
	{
		Rigidbody2D& rigidbody = getComponent<Rigidbody2D>();
		rigidbody.addEnterCollisionEvent(bind(&ScriptComponent::onCollisionEnter2D, this, placeholders::_1));
		rigidbody.addExitCollisionEvent(bind(&ScriptComponent::onCollisionExit2D, this, placeholders::_1));
	}
}

ScriptComponent* ScriptComponent::doClone()
{
	return new ScriptComponent(*this);
}
