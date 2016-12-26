/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "game_scene.hpp"

#include "game_data.hpp"
#include "game_object_2d.hpp"
#include "sprite.hpp"
#include "transform_2d.hpp"

GameScene::GameScene(SceneHandler* handler): Scene(handler)
{
	//guiView.setSize(sf::Vector2f(GameData::instance().window.getSize()));
	//guiView.setCenter(sf::Vector2f(GameData::instance().window.getSize()) * 0.5f);
}

void GameScene::hierarchy()
{
	// Creating game objects
	GameObject2D* a = new GameObject2D("Alien");
	a->addComponent<Sprite>("alien");

	// Initializing game objects' values
	//a->getComponent<Sprite>().setSpriteAnchor(sf::Vector2f(0.5f, 0.5f));
	a->getComponent<Transform2D>().setPosition(sf::Vector2f(2, 1));
	//a->getComponent<Transform2D>().setRotation(45);

	// Add to hierarchy root
	addToRoot(a);
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	Scene::draw(target, states);

	//target.setView(guiView);
}
