/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_game.hpp"

Core::Core(Data* gameData) : data(gameData)
{
	//Load everything needed
	loadResources();
	
	// Create window
	data->window.create(sf::VideoMode(800, 600),
						"Prototype - Project Phronesis");//,
						//sf::Style::Titlebar | sf::Style::Close);
	data->window.setFramerateLimit(60);
	
	// Resize and close window action based on Thor's ActionMap
	data->inputSystem["resize"] = thor::Action(sf::Event::Resized);
	data->inputSystem["quit"] = thor::Action(sf::Event::Closed);
	
	// Pass data to stack, so every states get it
	states.acquireData(data);
	
	// Register states, then push the first state
	registerStates();
	states.pushState("Title");
}

void Core::run()
{
	sf::Clock clock;

    while(data->window.isOpen())
    {
		//(Re)Start a timer at the beginning of each frame
        //after storing the time elapsed as dt
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
		
		//Poll the window for new events, update actions
        data->inputSystem.update(data->window);
		
		inputHandling();
		update(dt);
		draw();
	}
}

void Core::inputHandling()
{
	if(data->inputSystem.isActive("quit"))
		data->window.close();
	
	// All other input from the states
	states.handleEvent();
}

void Core::update(float dt)
{
	states.update(dt);
	data->animStorage.updateAll(dt);
}

void Core::draw()
{
	//Clear the window with black color
	data->window.clear(sf::Color::Black);
	
	//Draw everything here...
	states.draw();

	//End the current frame
	data->window.display();
}

void Core::loadResources()
{
	//Example code:
	//data->store.loadTexture("background", "assets/image.png");
	//data->store.loadFont("titleFont", "assets/font.ttf");
	//data->store.loadSfx("gameOver", "assets/lose.ogg");
}

// Registering states with different type of class
// to be fit into the states stack
void Core::registerStates()
{
	states.registerState<TitleState>("Title");
	states.registerState<MenuState>("Menu");
	states.registerState<GameState>("Game");
	states.registerState<PauseState>("Pause");
}