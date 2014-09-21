/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_game.hpp"

Core::Core()
{
	window.create(sf::VideoMode(800, 600), "Prototype - Project Phronesis",
                  sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
}

void Core::run()
{
	sf::Clock clock;

    while(window.isOpen())
    {
		//(Re)Start a timer at the beginning of each frame
        //Stop it at the end, before storing the time elapsed
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
        //dt will be passed to any functions that
        //need to know the speed of the game
		
		// Poll the window for new events, update actions
        inputSystem.update(window);
		inputReact();
		
		// clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
	}
}

void Core::inputReact()
{
	thor::Action clx(sf::Event::Closed);
	inputSystem["quit"] = clx;
	
	if(inputSystem.isActive("quit"))
		window.close();
}
