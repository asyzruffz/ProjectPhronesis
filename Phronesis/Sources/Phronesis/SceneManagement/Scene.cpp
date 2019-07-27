
#include "StdAfx.hpp"
#include "Scene.hpp"

using namespace Phronesis;

Scene::Scene() :
	isStarted(false),
	root(std::make_shared<Entity>())
{
}

void Scene::start()
{
}

void Scene::update()
{
}

Entity::Ptr Scene::createEntity()
{
	return addToRoot(new Entity);
}

bool Scene::hasStarted()
{
	return isStarted;
}

void Scene::setStarted()
{
	isStarted = true;
}

void Scene::internalStart()
{
	root->start();
	start();
}

void Scene::internalUpdate()
{
	root->update();
	update();
}

Entity::Ptr Scene::addToRoot(Entity* newEntity)
{
	return newEntity->setParent(root);
}
