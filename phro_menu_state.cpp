/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_menu_state.hpp"

MenuState::MenuState(Data* gameData, StateStack* stack)
{
	data = gameData;
	mStack = stack;
}

void MenuState::draw()
{
	data->window.clear(sf::Color::Green);
}

bool MenuState::update(float dt)
{
	return true;
}

bool MenuState::handleEvent()
{
	return true;
}
