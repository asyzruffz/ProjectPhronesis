/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_GAME_STATE_HPP
#define PHRO_GAME_STATE_HPP

#include <SFML/Graphics.hpp>

#include "../phro_state.hpp"
#include "../phro_data.hpp"
#include "../mechanics/phro_section.hpp"

class GameState : public State
{
public:
	
	GameState(Data* gameData, StateStack* stack);
	
	void draw();
	bool update(float dt);
	bool handleEvent();
	
private:
	
	sf::View gameView;
	sf::View guiView;
	
	Section area;
	
	void loadResources();
};

#endif // PHRO_GAME_STATE_HPP
