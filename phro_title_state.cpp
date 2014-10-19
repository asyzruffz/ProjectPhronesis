/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_title_state.hpp"

TitleState::TitleState(Data* gameData)
{
	data = gameData;
	
	//Additional load for this state
	loadResources();
	
	data->inputSystem["hover"] = thor::Action(sf::Event::MouseMoved);
	data->inputSystem["rightwalk"] = thor::Action(sf::Keyboard::D);
	data->inputSystem["brake"] = thor::Action(sf::Keyboard::A);
	data->inputSystem["jump"] = thor::Action(sf::Keyboard::Space);
}

void TitleState::draw()
{
	data->window.clear(sf::Color::Blue);
	
	data->window.draw(data->animStorage.animList["roboegg"]);
	//data->window.draw(test);
}

bool TitleState::update(float dt)
{
	return true;
}

bool TitleState::handleEvent()
{
	if(data->inputSystem.isActive("jump"))
		data->animStorage.animList["roboegg"].play("jump", false);
	else if(data->inputSystem.isActive("rightwalk"))
		data->animStorage.animList["roboegg"].play("walk");
	else if(data->inputSystem.isActive("brake"))
		data->animStorage.animList["roboegg"].stop();
	else if(!data->animStorage.animList["roboegg"].isPlaying())
		data->animStorage.animList["roboegg"].play("default");
	
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
}
