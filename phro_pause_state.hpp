/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_PAUSE_STATE_HPP
#define PHRO_PAUSE_STATE_HPP

#include <SFML/Graphics.hpp>

#include "phro_state.hpp"
#include "phro_data.hpp"

class PauseState : public State
{
public:
	
	PauseState(Data* gameData);
	
	void draw();
	bool update(float dt);
	bool handleEvent();
	
private:
	
	//some variables here
};

#endif // PHRO_PAUSE_STATE_HPP
