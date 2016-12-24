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

void Scene::requestSceneChange(const int& sceneIndex)
{
	mp_handler->changeScene(sceneIndex);
}

void Scene::requestSceneClear()
{
	mp_handler->clearScenes();
}
