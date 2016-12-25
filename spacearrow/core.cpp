/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#include "core.hpp"

#include <iostream>
#include <exception>
using namespace std;

#include "game_data.hpp"
#include "game_scene.hpp" // Scene to be registered

Core::Core(string gameTitle)
{
	try
	{

		//Load everything needed
		loadResources();
	
		// Create window
		m_window.create(sf::VideoMode(800, 600), gameTitle);//,
										//sf::Style::Titlebar | sf::Style::Close);
		m_window.setFramerateLimit(60);
	
		// Register states, then push the first state
		registerScenes();
		m_scenes.changeScene(0);

	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Error: Unknown exception thrown!" << endl;
	}
}

void Core::run()
{
	try
	{

		sf::Clock clock;

		while(m_window.isOpen())
		{
			//(Re)Start a timer at the beginning of each frame
			//after storing the time elapsed as dt
			sf::Time elapsed = clock.restart();
			float dt = elapsed.asSeconds();
		
			//Poll the window for new events, update actions
			//data->inputSystem.update(data->window);
		
			inputHandling();
			update(dt);
			draw(m_window);
		}

	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Error: Unknown exception thrown!" << endl;
	}
}

void Core::inputHandling()
{
	sf::Event gameEvent;

	// while there are pending events...
	while (m_window.pollEvent(gameEvent))
	{
		// check the type of the event...
		switch (gameEvent.type)
		{
			// window closed
			case sf::Event::Closed:
				m_window.close();
				break;

			// key pressed
			case sf::Event::KeyPressed:
				//...
				break;

			// we don't process other types of events
			default:
				break;
		}
	}
	
	// All other input from the states
	m_scenes.handleEvent();
}

void Core::update(float dt)
{
	m_scenes.update(dt);
	//data->animStorage.updateAll(dt);
}

void Core::draw(sf::RenderWindow& window) const
{
	//Clear the window with cornflower blue color
	window.clear(sf::Color(100, 149, 237));
	
	//Draw everything here...
	m_scenes.draw(window, m_renderStates);

	//End the current frame
	window.display();
}

void Core::loadResources()
{
	//Example code:
	//GameData::instance().rscStorage.loadTexture("background", "assets/image.png");
	//GameData::instance().rscStorage.loadFont("titleFont", "assets/font.ttf");
	//GameData::instance().rscStorage.loadSfx("gameOver", "assets/lose.ogg");

	GameData::instance().rscStorage.loadTexture("alien", "resources/alienGreen_square.png");
}

// Registering scenes with different type of class
// to be stored into the scene storage
void Core::registerScenes()
{
	m_scenes.registerScene<GameScene>();
}
