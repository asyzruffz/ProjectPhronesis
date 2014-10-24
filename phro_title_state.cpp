/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

#include "phro_title_state.hpp"

TitleState::TitleState(Data* gameData)
{
	data = gameData;
	
	//Additional load for this state
	loadResources();
	
	for(int i = 0; i < 3; i++)
		rgb[i] = 0;
	
	//data->inputSystem["hover"] = thor::Action(sf::Event::MouseMoved);
	data->inputSystem["rightwalk"] = thor::Action(sf::Keyboard::D);
	data->inputSystem["brake"] = thor::Action(sf::Keyboard::A);
	data->inputSystem["jump"] = thor::Action(sf::Keyboard::Space);
}

void TitleState::draw()
{
	data->window.clear(sf::Color(rgb[0], rgb[1], rgb[2]));
	
	data->window.draw(data->animStorage.animList["blue_button"]);
	data->window.draw(data->animStorage.animList["roboegg"]);
}

bool TitleState::update(float dt)
{
	int chooseColour = rand() % 3;
	rgb[chooseColour]++;
	for(int i = 0; i < 3; i++)
		if(rgb[i] == 255)
			rgb[i] = 0;
	
	return true;
}

bool TitleState::handleEvent()
{
	sf::Vector2i pointerPos = sf::Mouse::getPosition(data->window);
	
	if(data->animStorage.animList["blue_button"].clicked(pointerPos))
		goMainMenu();
	
	if(data->inputSystem.isActive("jump"))
		data->animStorage.animList["roboegg"].play("jump", false);
	else if(data->inputSystem.isActive("rightwalk"))
		data->animStorage.animList["roboegg"].play("walk");
	else if(data->inputSystem.isActive("brake"))
		data->animStorage.animList["roboegg"].stop();
	else if(!data->animStorage.animList["roboegg"].isPlaying())
		data->animStorage.animList["roboegg"].play("walk");
	
	return true;
}

void TitleState::loadResources()
{
	//Example code:
	//data->rscStorage.loadTexture("background", "assets/image.png");
	//data->rscStorage.loadFont("titleFont", "assets/font.ttf");
	//data->rscStorage.loadSfx("gameOver", "assets/lose.ogg");
	
	sf::Vector2f screenCenter = sf::Vector2f(data->window.getSize()) * 0.5f;
	
	data->rscStorage.loadTexture("roboegg", "assets/animations/roboegg.png");
	data->animStorage.addAnim("roboegg", "assets/animations");
	data->animStorage.animList["roboegg"].setOrigin(35, 31);
	data->animStorage.animList["roboegg"].setPosition(screenCenter.x, 400.f);
	
	data->rscStorage.loadTexture("blue_button", "assets/animations/blue_button.png");
	data->animStorage.addAnim("blue_button", "assets/animations");
	data->animStorage.animList["blue_button"].setOrigin(90, 24);
	data->animStorage.animList["blue_button"].setPosition(screenCenter);
}

void TitleState::goMainMenu()
{
	cout << "Title Screen: Going to Main Menu!" << endl;
}
