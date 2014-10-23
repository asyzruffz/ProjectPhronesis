/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_TITLE_STATE_HPP
#define PHRO_TITLE_STATE_HPP

#include <SFML/Graphics.hpp>

#include "phro_state.hpp"
#include "phro_data.hpp"

class TitleState : public State
{
public:
	
	TitleState(Data* gameData);
	
	void draw();
	bool update(float dt);
	bool handleEvent();
	
	void loadResources();
	
private:
	
	//some variables here
	sf::Sprite test;
};

#endif // PHRO_TITLE_STATE_HPP
