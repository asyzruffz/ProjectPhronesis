/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_STATE_HPP
#define PHRO_STATE_HPP

#include <string>
#include <memory>
using namespace std;

#include "phro_data.hpp"

class StateStack;

class State
{
public:
	
	State(Data* gameData);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(float dt) = 0;
	virtual bool handleEvent() = 0;
	
	typedef unique_ptr<State> Ptr;
	
protected:
	
	void requestStackPush(string stateID);
	void requestStackPop();
	void requestStateClear();
	
private:
	
	Data* data;
	StateStack*	mStack;
};

#endif // PHRO_STATE_HPP
