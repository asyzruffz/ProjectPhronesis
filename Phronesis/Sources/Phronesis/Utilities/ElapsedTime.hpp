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

		void setInterval(const Time& time);
		const Time& getInterval() const;

	private:
		Time startTime;
		Time interval;
	};
}
