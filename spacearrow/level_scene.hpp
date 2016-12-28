/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef LEVEL_SCENE_HPP
#define LEVEL_SCENE_HPP

#include <SFML/Graphics.hpp>

#include "scene.hpp"

class LevelScene : public Scene
{
public:
	
	LevelScene(SceneHandler* handler) : Scene(handler) {}

	void hierarchy();
	
};

#endif // LEVEL_SCENE_HPP