/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_title_state.hpp"

TitleState::TitleState(Data* gameData)
{
	data = gameData;
	
	//Additional load for this state
	loadResources();
}

void TitleState::draw()
{
	data->window.clear(sf::Color::Blue);
}

bool TitleState::update(float dt)
{
	return true;
}

bool TitleState::handleEvent()
{
	return true;
}

void TitleState::loadResources()
{
	//Example code:
	//data->store.loadTexture("background", "assets/image.png");
	//data->store.loadFont("titleFont", "assets/font.ttf");
	//data->store.loadSfx("gameOver", "assets/lose.ogg");
}
