/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_DATA_HPP
#define PHRO_DATA_HPP

#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

class Data
{
public:
	
	sf::RenderWindow window;
	
	thor::ActionMap<string> inputSystem;
};

#endif // PHRO_DATA_HPP