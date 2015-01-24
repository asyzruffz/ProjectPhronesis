/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

#include "phro_title_state.hpp"

TitleState::TitleState(Data* gameData, StateStack* stack): State(gameData, stack)
{
	//Additional load for this state
	loadResources();
	
	view.setSize(sf::Vector2f(data->window.getSize()));
	view.setCenter(sf::Vector2f(data->window.getSize()) * 0.5f);
	
	for(int i = 0; i < 3; i++)
		rgb[i] = 0;
	
	//data->inputSystem["hover"] = thor::Action(sf::Event::MouseMoved);
	data->inputSystem["rightwalk"] = thor::Action(sf::Keyboard::D);
	data->inputSystem["leftwalk"] = thor::Action(sf::Keyboard::A);
	data->inputSystem["duck"] = thor::Action(sf::Keyboard::S);
	data->inputSystem["jump"] = thor::Action(sf::Keyboard::Space);
}

void TitleState::draw()
{
	data->window.clear(sf::Color(rgb[0], rgb[1], rgb[2]));
	data->window.setView(view);
	
	data->window.draw(data->animStorage.animList["blue_button"]);
	data->window.draw(data->animStorage.animList["roboegg"]);
	data->window.draw(al);
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
	if(data->inputSystem.isActive("resize"))
	{
		view.setSize(sf::Vector2f(data->window.getSize()));
		view.setCenter(sf::Vector2f(data->window.getSize()) * 0.5f);
		
		sf::Vector2f screenCenter = sf::Vector2f(data->window.getSize()) * 0.5f;
		screenCenter = data->window.mapPixelToCoords(sf::Vector2i(screenCenter), view);
		
		data->animStorage.animList["blue_button"].setPosition(screenCenter);
		data->animStorage.animList["roboegg"].setPosition(screenCenter.x, screenCenter.y+100.f);
		al.setPosition(screenCenter.x, screenCenter.y-150.f);
	}
	
	sf::Vector2i pointerPos = sf::Mouse::getPosition(data->window);
	
	if(data->animStorage.animList["blue_button"].clicked(pointerPos))
		goMainMenu();
	
	if(data->inputSystem.isActive("jump"))
		data->animStorage.animList["roboegg"].play("jump", false);
	else if(data->inputSystem.isActive("rightwalk"))
		data->animStorage.animList["roboegg"].setScale(1.f, 1.f);
	else if(data->inputSystem.isActive("leftwalk"))
		data->animStorage.animList["roboegg"].setScale(-1.f, 1.f);
	else if(!data->animStorage.animList["roboegg"].isPlaying())
		data->animStorage.animList["roboegg"].play("walk");
	
	if(data->inputSystem.isActive("duck"))
		data->animStorage.animList["greenalien"].play("duck", false);
	else if(data->inputSystem.isActive("jump"))
		data->animStorage.animList["greenalien"].play("jump", false);
	else if(data->inputSystem.isActive("rightwalk"))
		al.setScale(1.f, 1.f);
	else if(data->inputSystem.isActive("leftwalk"))
		al.setScale(-1.f, 1.f);
	else if(!data->animStorage.animList["greenalien"].isPlaying())
		data->animStorage.animList["greenalien"].play("walk");

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
	data->animStorage.animList["roboegg"].setPosition(screenCenter.x, screenCenter.y+100.f);
	
	data->rscStorage.loadTexture("greenalien", "assets/characters/greenalien.png");
	data->animStorage.addAnim("greenalien", "assets/characters");
	
	al.setCharacter("greenalien", &data->animStorage);
	al.setPosition(screenCenter.x, screenCenter.y-150.f);
	
	data->rscStorage.loadTexture("blue_button", "assets/buttons/blue_button.png");
	data->animStorage.addAnim("blue_button", "assets/buttons");
	data->animStorage.animList["blue_button"].setPosition(screenCenter);
}

void TitleState::goMainMenu()
{
	requestStackPop();
	requestStackPush("Game");
}
