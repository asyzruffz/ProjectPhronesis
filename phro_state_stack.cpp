/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_state_stack.hpp"

template <typename T>
void StateStack::registerState(string stateID, Data* gameData)
{
	mFactories[stateID] = [this] (Data* gameData)
	{
		return State::Ptr(new T(gameData));
	};
}

void StateStack::update(float dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	// Draw all active states from bottom to top
	for(int i = 0; i < mStack.size(); i++)
		mStack[i]->draw();
}

void StateStack::handleEvent()
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent())
			break;
	}

	applyPendingChanges();
}
	
void StateStack::pushState(string stateID)
{
	mPendingList.push_back(make_pair("push", stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(make_pair("pop", ""));
}

void StateStack::clearStates()
{
	mPendingList.push_back(make_pair("clear", ""));
}
	
bool StateStack::isEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::createState(string stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for(int i = 0; i < mPendingList.size(); i++)
	{
		if(mPendingList[i].first == "push")
			mStack.push_back(createState(mPendingList[i].second));
		else if(mPendingList[i].first == "pop")
			mStack.pop_back();
		else if(mPendingList[i].first == "clear")
			mStack.clear();
	}
	
	mPendingList.clear();
}
