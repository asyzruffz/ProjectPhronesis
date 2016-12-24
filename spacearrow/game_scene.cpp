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
	//emptyWorld = new World(data);
	
	guiView.setSize(sf::Vector2f(GameData::instance().window.getSize()));
	guiView.setCenter(sf::Vector2f(GameData::instance().window.getSize()) * 0.5f);
	
	//area = Section(10, 8, "assets/plain.section");
	//area = Section(16, 11, "assets/test.section");
	//area.acquireResource(&data->rscStorage);
}

GameScene::~GameScene()
{
	//delete emptyWorld;
}

void GameScene::draw()
{
	GameData::instance().window.clear(sf::Color::Red);
	
	//emptyWorld->draw();
	
	GameData::instance().window.setView(guiView);
	//area.draw(data->window);
}

bool GameScene::update(float dt)
{
	//area.updateTileVariant();
	//emptyWorld->update(dt);
	return true;
}

bool GameScene::handleEvent()
{
	/*if(data->inputSystem.isActive("resize"))
	{
		guiView.setSize(sf::Vector2f(data->window.getSize()));
		guiView.setCenter(sf::Vector2f(data->window.getSize()) * 0.5f);
		
		emptyWorld->resizeView();
	}*/
	
	return true;
}
