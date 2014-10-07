/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_title_state.hpp"

TitleState::TitleState(Data* gameData)
{
	data = gameData;
	
	//Additional load for this state
	loadResources();
	
	thor::Action hvr(sf::Event::MouseMoved);
	data->inputSystem["hover"] = hvr;
}

void TitleState::draw()
{
	data->window.clear(sf::Color::Blue);

	data->animStorage.animCollection["roboegg"].animate(test);
	data->window.draw(test);
}

bool TitleState::update(float dt)
{
	return true;
}

bool TitleState::handleEvent()
{
	if(data->inputSystem.isActive("hover"))
		data->animStorage.animCollection["roboegg"].play("fall");
	
	return true;
}

void TitleState::loadResources()
{
	//Example code:
	//data->rscStorage.loadTexture("background", "assets/image.png");
	//data->rscStorage.loadFont("titleFont", "assets/font.ttf");
	//data->rscStorage.loadSfx("gameOver", "assets/lose.ogg");

	data->rscStorage.loadTexture("roboegg", "assets/animations/roboegg.png");
	data->animStorage.addAnim("roboegg", "assets/animations");
	test.setTexture(data->rscStorage.getTextureRef("roboegg"));
}
