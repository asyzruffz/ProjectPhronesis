/***** P R O J E C T   P H R O N E S I S *****
*********************************************/

#include "phro_state_stack.hpp"

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
	Pending push;
	push.action = "push";
	push.stateType = stateID;
	mPendingList.push_back(push);
}

void StateStack::popState()
{
	Pending pop;
	pop.action = "pop";
	pop.stateType = "";
	mPendingList.push_back(pop);
}

void StateStack::clearStates()
{
	Pending clear;
	clear.action = "clear";
	clear.stateType = "";
	mPendingList.push_back(clear);
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
		if(mPendingList[i].action == "push")
			mStack.push_back(createState(mPendingList[i].stateType));
		else if(mPendingList[i].action == "pop")
			mStack.pop_back();
		else if(mPendingList[i].action == "clear")
			mStack.clear();
	}
	
	mPendingList.clear();
}

void StateStack::acquireData(Data* data)
{
	gameData = data;
}
