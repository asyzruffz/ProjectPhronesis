/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_pause_state.hpp"

PauseState::PauseState(Data* gameData)
{
	data = gameData;
}

void PauseState::draw()
{
	data->window.clear(sf::Color::Yellow);
}

bool PauseState::update(float dt)
{
	return true;
}

bool PauseState::handleEvent()
{
	return true;
}
