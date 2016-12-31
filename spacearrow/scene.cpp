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
#include "game_object.hpp"

b2World Scene::world(b2Vec2(0.0f, 9.81f));
ContactListener2D Scene::contactListenerInstance;

Scene::Scene(SceneHandler* handler) : mp_handler(handler)
{
	m_fixedTimeStep = 0.02f; // 50 times per second
	m_timeElapsed = 0;

	mp_root = make_shared<GameObject>(GameObject("Root"));

	// Initialize world
	world.SetContactListener(&contactListenerInstance);
}

void Scene::start()
{
	//Call hierarchy to add gameobjects to scene
	hierarchy();
	
	//Call the start method for each child of root
	for (vector<Entity::Ptr>::size_type i = 0; i < mp_root->getChildren().size(); i++)
	{
		static_pointer_cast<GameObject>(mp_root->getChildren()[i])->start();
	}
}

void Scene::handleEvent()
{
	return;
}

void Scene::update(float dt)
{
	//Call the update method for each child of root
	for (vector<Entity::Ptr>::size_type i = 0; i < mp_root->getChildren().size(); i++)
	{
		static_pointer_cast<GameObject>(mp_root->getChildren()[i])->update(dt);
	}

	if (m_timeElapsed >= m_fixedTimeStep)
	{
		// Step is used to update physics position/rotation
		world.Step(m_fixedTimeStep,	//update frequency
					8,				//velocityIterations
					3				//positionIterations  
		);
		
		//Call fixedUpdate method for each child of root
		for (vector<Entity::Ptr>::size_type i = 0; i < mp_root->getChildren().size(); i++)
		{
			static_pointer_cast<GameObject>(mp_root->getChildren()[i])->fixedUpdate(dt);
		}

		m_timeElapsed -= m_fixedTimeStep;
	}

	m_timeElapsed += dt;
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Call the draw method for each child of root
	for (vector<Entity::Ptr>::size_type i = 0; i < mp_root->allChildren().size(); i++)
	{
		static_pointer_cast<GameObject>(mp_root->allChildren()[i])->draw(target, states);
	}
}

Entity::Ptr Scene::addToRoot(GameObject* gameObject)
{
	return gameObject->setParent(mp_root);
}

void Scene::requestSceneChange(const int& sceneIndex)
{
	mp_handler->changeScene(sceneIndex);
}

void Scene::requestSceneClear()
{
	mp_handler->clearScenes();
}
