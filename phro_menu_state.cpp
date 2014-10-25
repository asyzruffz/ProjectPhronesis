/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_menu_state.hpp"

MenuState::MenuState(Data* gameData, StateStack* stack)
{
	data = gameData;
	mStack = stack;
	
	//Additional load for this state
	loadResources();
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

void MenuState::loadResources()
{
	//Example code:
	//data->rscStorage.loadTexture("background", "assets/image.png");
	//data->rscStorage.loadFont("titleFont", "assets/font.ttf");
	//data->rscStorage.loadSfx("gameOver", "assets/lose.ogg");
}
