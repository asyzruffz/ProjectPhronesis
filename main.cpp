/***** P R O J E C T   P H R O N E S I S *****
Author Name #1 : Muhammad Asyraf bin Ibrahim
Contacts #1 : +60134642899 asyzruffz@gmail.com
Author Name #2 :
Contacts #2 :
Author Name #3 :
Contacts #3 :
*********************************************/

#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

#include <iostream>
#include <string>
using namespace std;

//#include "game.hpp"
//#include "game_state_start.hpp"

int main()
{
    //Game game;

    //game.changeState(GameStateStart(&game));
    //game.gameLoop();
    thor::Action clx(sf::Event::Closed);

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    thor::ActionMap<string> step;

    step["close"] = clx;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // Poll the window for new events, update actions
        step.update(window);

        if (step.isActive("close"))
            window.close();

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}
