#pragma once

#include <memory>
#include <vector>

#include "Game.hpp"

namespace Phronesis
{
	class Engine
	{
	public:
		Engine(char** argv, int argc);
		~Engine();

		void setGame(Game* newGame);
		void run();

	private:
		std::vector<std::string> args;

		std::unique_ptr<Game> game;
	};
}
