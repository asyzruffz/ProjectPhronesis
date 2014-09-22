/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_GAME_STATE_HPP
#define PHRO_GAME_STATE_HPP

#include <SFML/Graphics.hpp>

#include "phro_state.hpp"
#include "phro_data.hpp"

class GameState : public State
{
public:
	
	GameState(Data* gameData);
	
	void draw();
	bool update(float dt);
	bool handleEvent();
	
private:
	
	//some variables here
};

#endif // PHRO_GAME_STATE_HPP
