/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
using namespace std;

#include "game_object_2d.hpp"

// Forward declaration to avoid cyclic dependency
class SceneHandler;

class Scene
{
public:
	
	Scene(){}
	Scene(SceneHandler* handler): mp_handler(handler) {}
	virtual ~Scene() {}

	typedef unique_ptr<Scene> Ptr;

	virtual void hierarchy() = 0;

	virtual void start();
	virtual bool handleEvent();
	virtual bool update(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void addToRoot(GameObject* gameObject);

protected:
	
	void requestSceneChange(const int& sceneIndex);
	void requestSceneClear();
	
	SceneHandler* mp_handler;

private:

	GameObject2D m_root;

};

#endif // SCENE_HPP
