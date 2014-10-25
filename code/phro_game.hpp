/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_GAME_HPP
#define PHRO_GAME_HPP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
using namespace std;

#include "phro_data.hpp"
#include "phro_state_stack.hpp"
#include "states/phro_title_state.hpp"
#include "states/phro_menu_state.hpp"
#include "states/phro_game_state.hpp"
#include "states/phro_pause_state.hpp"

// The core of the game handling all of the states

class Core
{
public:

	Core(Data* gameData);

	void run();				// main loop

	void inputHandling();	// The big 3 functions
	void update(float dt);	// running in a loop
	void draw();			//

	void loadResources();

	void registerStates();

	StateStack states;

private:

	Data* data;

};

#endif // PHRO_GAME_HPP
