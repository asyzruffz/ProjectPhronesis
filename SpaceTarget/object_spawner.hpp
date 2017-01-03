/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef OBJECT_SPAWNER_HPP
#define OBJECT_SPAWNER_HPP

#include "script_component.hpp"

class ObjectSpawner : public ScriptComponent
{
public:

	ObjectSpawner(GameObject* objectToSpawn);

	void start();
	Entity::Ptr spawn(const sf::Vector2f& position, const float& rotation);

private:

	unique_ptr<GameObject> mp_objectTemplate;
};

#endif // OBJECT_SPAWNER_HPP