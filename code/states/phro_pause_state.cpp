/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_pause_state.hpp"

PauseState::PauseState(Data* gameData, StateStack* stack)
{
	data = gameData;
	mStack = stack;
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
