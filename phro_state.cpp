/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_state.hpp"
#include "phro_state_stack.hpp"

State::State(Data* gameData)
: data(gameData)
{}

State::~State()
{}

void State::requestStackPush(string stateID)
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
