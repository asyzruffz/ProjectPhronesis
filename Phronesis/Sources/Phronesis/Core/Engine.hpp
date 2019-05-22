#pragma once

#include <memory>
#include <vector>

namespace Phronesis
{
	class Game;

	class Engine
	{
	public:
		static Engine* Get();
		Engine(char** argv, int argc);
		~Engine();

		void setGame(Game* newGame);
		Game& getGame();

		void run();

		bool isRunning() const;
		void stop();

	private:
		std::vector<std::string> args;
		static Engine* instance;
		bool running;

		std::unique_ptr<Game> game;
	};
}
