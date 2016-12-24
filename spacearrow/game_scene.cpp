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

GameScene::GameScene(SceneHandler* handler): Scene(handler)
{
	//guiView.setSize(sf::Vector2f(GameData::instance().window.getSize()));
	//guiView.setCenter(sf::Vector2f(GameData::instance().window.getSize()) * 0.5f);
}

void GameScene::hierarchy()
{
	
}

void GameScene::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
	window.clear(sf::Color::Red);

	//emptyWorld->draw();

	window.setView(guiView);
}
