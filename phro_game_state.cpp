/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_game_state.hpp"

GameState::GameState(Data* gameData)
{
	data = gameData;
	
	//Additional load for this state
	loadResources();
}

void GameState::draw()
{
	data->window.clear(sf::Color::Red);
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
	//Example code:
	//data->rscStorage.loadTexture("background", "assets/image.png");
	//data->rscStorage.loadFont("titleFont", "assets/font.ttf");
	//data->rscStorage.loadSfx("gameOver", "assets/lose.ogg");
}
