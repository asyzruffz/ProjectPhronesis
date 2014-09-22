/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_GAME_HPP
#define PHRO_GAME_HPP

#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include "phro_data.hpp"
#include "phro_state_stack.hpp"

class Core
{
public:
	
	Core(Data* gameData);
	
	void run();
	void inputReact();
	
	StateStack states;
	
private:
	
	Data* data;
	
};

#endif // PHRO_GAME_HPP
