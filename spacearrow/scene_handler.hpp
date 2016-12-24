/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef SCENE_HANDLER_HPP
#define SCENE_HANDLER_HPP

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
using namespace std;

#include "game_data.hpp"
#include "scene.hpp"

struct Pending
{
	string action;
	int sceneIndex;
	
	Pending(string action_, int sceneIndex_) : action(action_), sceneIndex(sceneIndex_) {}
};

class SceneHandler : private sf::NonCopyable
{
public:
	
	SceneHandler();
	
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void handleEvent();

	template <typename T>
	void registerScene();

	//These actions are not done immediately
	//(change, clear) are put in a pending list first
	//so that it can be executed when it is safe
	void changeScene(int sceneIndex);
	void clearScenes();
	
	bool isEmpty() const;
	
private:
	
	//Do the pending change or clear of scenes when it's safe
	void applyPendingChanges();
	
	//Storage containing the scenes (pointer to Scene)
	vector<Scene::Ptr> m_storage;
	//Pending lists of (action and state type) pair (e.g: "Change", "Clear")
	vector<Pending> m_pendingList;
	//Index of the scene currently updated
	int m_currentScene;
};

// Since all scenes are different datatypes (class),
// we 'register' it to be a function that return a pointer to Scene
template <typename T>
void SceneHandler::registerScene()
{
	m_storage.push_back(Scene::Ptr(new T(this)));
}

#endif // SCENE_HANDLER_HPP
