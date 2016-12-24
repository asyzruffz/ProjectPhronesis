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

#include "game_data.hpp"

class SceneHandler;

class Scene
{
public:
	
	Scene(){}
	Scene(SceneHandler* handler): mp_handler(handler) {}
	virtual ~Scene() {}

	virtual bool handleEvent() = 0;
	virtual bool update(float dt) = 0;
	virtual void draw() = 0;
	
	typedef unique_ptr<Scene> Ptr;
	
protected:
	
	void requestSceneChange(const int& sceneIndex);
	void requestSceneClear();
	
	SceneHandler* mp_handler;
};

#endif // SCENE_HPP
