
#include "StdAfx.hpp"
#include "TimeUpdate.hpp"

using namespace Phronesis;

void Delta::update()
{
	currentFrameTime = Time::now();
	change = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
}

const Time& Delta::getChange() const
{
	return change;
}

void ChangePerSecond::update(const Time& time)
{
	valueTemp++;

	if(std::floor(time.asSeconds()) > std::floor(valueTime.asSeconds()))
	{
		value = valueTemp;
		valueTemp = 0;
	}

	valueTime = time;
}

const unsigned int& ChangePerSecond::getValue() const
{
	return value;
}
