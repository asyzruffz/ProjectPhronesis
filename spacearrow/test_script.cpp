/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "test_script.hpp"

#include <iostream>
using namespace std;

#include "transform_2d.hpp"

void TestScript::start()
{
	ScriptComponent::start();
}

void TestScript::onCollisionEnter2D(GameObject& other)
{
	cout << "TestScript: " << getGameObject().getName() << " ("
		<< getGameObject().getComponent<Transform2D>().getGlobalPosition().x << ","
		<< getGameObject().getComponent<Transform2D>().getGlobalPosition().y
		<< ") start colliding with " << other.getName() << " ("
		<< other.getComponent<Transform2D>().getGlobalPosition().x << ","
		<< other.getComponent<Transform2D>().getGlobalPosition().y << ")" << endl;
}

void TestScript::onCollisionExit2D(GameObject& other)
{
	cout << "TestScript: " << getGameObject().getName() << " stop colliding with " << other.getName() << endl;
}
