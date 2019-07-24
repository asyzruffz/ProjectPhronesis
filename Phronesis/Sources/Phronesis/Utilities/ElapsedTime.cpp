
#include "StdAfx.hpp"
#include "ElapsedTime.hpp"

using namespace Phronesis;

ElapsedTime::ElapsedTime(const Time& interval) :
	startTime(Time::now()),
	interval(interval)
{
}

void ElapsedTime::start()
{
	startTime = Time::now();
}

unsigned int ElapsedTime::getElapsed()
{
	// before elapsing the interval: (elapsed == 0)
	// after elapsing: (elapsed == how many times it elapses the interval duration)
	auto now = Time::now();
	unsigned int elapsed = static_cast<unsigned int>(std::floor((now - startTime) / interval));

	// reset start time after elapsing
	if(elapsed != 0u)
	{
		startTime = now;
	}

	return elapsed;
}

void ElapsedTime::setStartTime(const Time& time)
{
	startTime = time;
}

void ElapsedTime::setInterval(const Time& time)
{
	interval = time;
}
