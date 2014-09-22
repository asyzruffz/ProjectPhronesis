/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#ifndef PHRO_STATE_STACK_HPP
#define PHRO_STATE_STACK_HPP

#include <SFML/Graphics.hpp>

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <cassert>
#include <functional>
using namespace std;

#include "phro_data.hpp"
#include "phro_state.hpp"

class StateStack : private sf::NonCopyable
{
public:
	
	StateStack(){}
	
	template <typename T>
	void registerState(string stateID);

	void update(float dt);
	void draw();
	void handleEvent();
	
	void pushState(string stateID);
	void popState();
	void clearStates();
	
	bool isEmpty() const;
	void getData(Data* gameData);
	
private:
	
	State::Ptr createState(string stateID);
	void applyPendingChanges();
	
	Data* gameData;
	std::vector<State::Ptr> mStack;
	std::vector<pair<string, string> > mPendingList;
	std::map<string, function<State::Ptr()> > mFactories;
};

template <typename T>
void StateStack::registerState(string stateID)
{
	mFactories[stateID] = [this] ()
	{
		return State::Ptr(new T(gameData));
	};
}

#endif // PHRO_STATE_STACK_HPP
