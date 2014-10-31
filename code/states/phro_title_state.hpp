/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_TITLE_STATE_HPP
#define PHRO_TITLE_STATE_HPP

#include <SFML/Graphics.hpp>

#include "../phro_state.hpp"
#include "../phro_data.hpp"

class TitleState : public State
{
public:

	TitleState(Data* gameData, StateStack* stack);

	void draw();
	bool update(float dt);
	bool handleEvent();

private:

	int rgb[3];
	sf::View view;

	void loadResources();
	void goMainMenu();
};

#endif // PHRO_TITLE_STATE_HPP
