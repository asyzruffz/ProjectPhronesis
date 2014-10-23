/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_STATE_STACK_HPP
#define PHRO_STATE_STACK_HPP

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <functional>
using namespace std;

#include "phro_data.hpp"
#include "phro_state.hpp"

struct Pending
{
	string action;
	string stateType;
	
	Pending(string action_, string stateType_) : action(action_), stateType(stateType_) {}
};

class StateStack : private sf::NonCopyable
{
public:
	
	StateStack(){}
	
	template <typename T>
	void registerState(string stateID);

	void update(float dt);
	void draw();
	void handleEvent();
	
	//These actions are not done immediately
	//(push, pop, clear) are put in a pending list first
	//so that it can be executed when it is safe
	void pushState(string stateID);
	void popState();
	void clearStates();
	
	bool isEmpty() const;
	
	//Acquire 'data' to be given to states
	void acquireData(Data* gameData);
	
private:
	
	//Convert the pending list to a State pointer
	State::Ptr createState(string stateID);
	//Do the pending push, pop or clear of states when it's safe
	void applyPendingChanges();
	
	Data* gameData;
	//Stack containing the states (pointer to state)
	std::vector<State::Ptr> mStack;
	//Pending lists of (action and state type) pair (e.g: "Push", "Pause")
	std::vector<Pending> mPendingList;
	//Factory storing the registered states
	std::map<string, function<State::Ptr()> > mFactories;
};

// Since all states are different datatypes (class),
// we 'register' it to be a function that return a pointer to State
template <typename T>
void StateStack::registerState(string stateID)
{
	mFactories[stateID] = [this] ()
	{
		return State::Ptr(new T(gameData));
	};
}

#endif // PHRO_STATE_STACK_HPP
