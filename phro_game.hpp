/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_GAME_HPP
#define PHRO_GAME_HPP

#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include "phro_data.hpp"
#include "phro_state_stack.hpp"
#include "phro_title_state.hpp"
#include "phro_menu_state.hpp"
#include "phro_game_state.hpp"
#include "phro_pause_state.hpp"

class Core
{
public:
	
	Core(Data* gameData);
	
	void run();
	void inputReact();
	void update(float dt);
	void draw();
	
	void registerStates();
	
	StateStack states;
	
private:
	
	Data* data;
	
};

#endif // PHRO_GAME_HPP
