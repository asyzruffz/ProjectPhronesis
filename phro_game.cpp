/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_game.hpp"

Core::Core(Data* gameData): data(gameData)
{
	data->window.create(sf::VideoMode(800, 600), "Prototype - Project Phronesis",
                  sf::Style::Titlebar | sf::Style::Close);
	data->window.setFramerateLimit(60);
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
		inputReact();
		
		//Clear the window with black color
        data->window.clear(sf::Color::Black);

        //Draw everything here...
        //data->window.draw(...);

        //End the current frame
        data->window.display();
	}
}

void Core::inputReact()
{
	thor::Action clx(sf::Event::Closed);
	data->inputSystem["quit"] = clx;
	
	if(data->inputSystem.isActive("quit"))
		data->window.close();
}
