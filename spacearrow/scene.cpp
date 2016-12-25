/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "scene.hpp"
#include "scene_handler.hpp"

void Scene::start()
{
	m_root = GameObject2D("Root");

	//Call hierarchy to add gameobjects to scene
	hierarchy();
	
	//Call the start method for each child of root
	for (vector<Entity::Ptr>::iterator it = m_root.getChildren().begin(); it != m_root.getChildren().end(); ++it)
	{
		static_pointer_cast<GameObject>(*it)->start();
	}
}

bool Scene::handleEvent()
{
	return false;
}

bool Scene::update(float dt)
{
	//Call the update method for each child of root
	for (vector<Entity::Ptr>::iterator it = m_root.getChildren().begin(); it != m_root.getChildren().end(); ++it)
	{
		static_pointer_cast<GameObject>(*it)->update(dt);
	}
	
	return false;
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Call the draw method for each child of root
	for (vector<Entity::Ptr>::const_iterator it = m_root.allChildren().begin(); it != m_root.allChildren().end(); ++it)
	{
		static_pointer_cast<GameObject>(*it)->draw(target, states);
	}
}

void Scene::addToRoot(GameObject* gameObject)
{
	gameObject->setParent(&m_root);
}

void Scene::requestSceneChange(const int& sceneIndex)
{
	mp_handler->changeScene(sceneIndex);
}

void Scene::requestSceneClear()
{
	mp_handler->clearScenes();
}
