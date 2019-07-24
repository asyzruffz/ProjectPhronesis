#pragma once

#include "Time.hpp"

namespace Phronesis
{
	class ElapsedTime
	{
	public:
		ElapsedTime(const Time& interval = Time::Seconds(-1));

		void start();
		unsigned int getElapsed();

		void setStartTime(const Time& time);
		void setInterval(const Time& time);

	private:
		Time startTime;
		Time interval;
	};
}
