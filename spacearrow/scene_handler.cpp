/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "scene_handler.hpp"

#include <iostream>
#include <cassert>
using namespace std;

SceneHandler::SceneHandler()
{
	m_currentScene = 0;
}

void SceneHandler::update(float dt)
{
	if (isEmpty())
	{
		cout << "No scene loaded!" << endl;
		return;
	}

	m_storage[m_currentScene]->update(dt);

	applyPendingChanges();
}

void SceneHandler::draw(sf::RenderWindow& window)
{
	if (isEmpty())
		return;
	
	// Draw current scene
	m_storage[m_currentScene]->draw(window);
}

void SceneHandler::handleEvent()
{
	if (isEmpty())
		return;

	m_storage[m_currentScene]->handleEvent();

	applyPendingChanges();
}
	
void SceneHandler::changeScene(int sceneIndex)
{
	Pending change("change", sceneIndex);
	m_pendingList.push_back(change);
}

void SceneHandler::clearScenes()
{
	Pending clear("clear", -1);
	m_pendingList.push_back(clear);
}

bool SceneHandler::isEmpty() const
{
	return m_storage.empty();
}

void SceneHandler::applyPendingChanges()
{
	for(int i = 0; i < m_pendingList.size(); i++)
	{
		if (m_pendingList[i].action == "change") {
			assert(m_pendingList[i].sceneIndex >= 0 && m_pendingList[i].sceneIndex < m_storage.size());
			m_currentScene = m_pendingList[i].sceneIndex;
		} else if (m_pendingList[i].action == "clear")
			m_storage.clear();
	}
	
	m_pendingList.clear();
}
