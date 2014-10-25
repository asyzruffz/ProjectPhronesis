/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_game_state.hpp"

GameState::GameState(Data* gameData, StateStack* stack)
{
	data = gameData;
	mStack = stack;
	
	//Additional load for this state
	loadResources();
	
	gameView.setSize(sf::Vector2f(data->window.getSize()));
	guiView.setSize(sf::Vector2f(data->window.getSize()));
	gameView.setCenter(sf::Vector2f(data->window.getSize()) * 0.5f);
	guiView.setCenter(sf::Vector2f(data->window.getSize()) * 0.5f);
	
}

void GameState::draw()
{
	data->window.clear(sf::Color::Red);
	
	data->window.setView(gameView);
	data->window.draw(dirt);
	
	data->window.setView(guiView);
	//data->window.draw(bla);
}

bool GameState::update(float dt)
{
	return true;
}

bool GameState::handleEvent()
{
	return true;
}

void GameState::loadResources()
{
	sf::Vector2f screenCenter = sf::Vector2f(data->window.getSize()) * 0.5f;
	
	data->rscStorage.loadTexture("dirt", "assets/tiles/rpgTile024.png");
	dirt.setTexture(data->rscStorage.getTextureRef("dirt"));
	dirt.setOrigin(32, 32);
	dirt.setPosition(screenCenter);
}
