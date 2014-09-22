/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_game_state.hpp"

GameState::GameState(Data* gameData)
{
	data = gameData;
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
