#pragma once

#include "Time.hpp"

namespace Phronesis
{
	class Delta
	{
	public:
		void update();
		const Time& getChange() const;

	private:
		Time currentFrameTime;
		Time lastFrameTime;
		Time change;
	};

	class ChangePerSecond
	{
	public:
		void update(const Time& time);
		const unsigned int& getValue() const;

	private:
		unsigned int value{}, valueTemp{};
		Time valueTime;
	};
}
