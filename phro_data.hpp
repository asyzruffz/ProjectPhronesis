/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_DATA_HPP
#define PHRO_DATA_HPP

#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

#include "phro_resource_manager.hpp"
#include "phro_animation_manager.hpp"

// A data class with a very wide scope so that
// its members can be accessed from anywhere
// or from any state.

class Data
{
public:
	
	sf::RenderWindow window;
	
	thor::ActionMap<string> inputSystem;
	
	ResourceManager rscStorage;
	
	AnimationManager animStorage;
	
	Data()
	{
		animStorage = AnimationManager(&rscStorage);
	}
};

#endif // PHRO_DATA_HPP
