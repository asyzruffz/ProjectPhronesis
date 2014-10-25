/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_state.hpp"
#include "phro_state_stack.hpp"

State::State(Data* gameData, StateStack* stack)
{
	data = gameData;
	mStack = stack;
}

State::~State()
{}

void State::requestStackPush(const string& stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}
