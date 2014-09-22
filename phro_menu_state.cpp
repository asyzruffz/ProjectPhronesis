/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_menu_state.hpp"

MenuState::MenuState(Data* gameData)
{
	data = gameData;
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
