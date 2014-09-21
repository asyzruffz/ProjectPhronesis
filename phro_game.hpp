/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_GAME_HPP
#define PHRO_GAME_HPP

#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

#include <iostream>
#include <string>
using namespace std;

class Core
{
private:
	
	sf::RenderWindow window;
	thor::ActionMap<string> inputSystem;
	
public:
	
	Core();
	
	void run();
	void inputReact();
};

#endif // PHRO_GAME_HPP
