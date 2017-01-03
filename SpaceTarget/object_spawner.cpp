/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "object_spawner.hpp"

#include "scene_handler.hpp"
#include "transform_2d.hpp"

ObjectSpawner::ObjectSpawner(GameObject* objectToSpawn)
{
	mp_objectTemplate = unique_ptr<GameObject>(new GameObject(*objectToSpawn));
}

void ObjectSpawner::start()
{
	
}

Entity::Ptr ObjectSpawner::spawn(const sf::Vector2f& position, const float& rotation)
{
	GameObject* newSpawn = new GameObject(*mp_objectTemplate);
	newSpawn->getComponent<Transform2D>().setGlobalPosition(position);
	newSpawn->getComponent<Transform2D>().setGlobalRotation(rotation);
	Entity::Ptr spawnedObject = SceneHandler::currentScene().addToRoot(newSpawn);
	newSpawn->start();
	return spawnedObject;
}
