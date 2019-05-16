#pragma once

#include "ModuleHandler.hpp"

namespace Phronesis
{
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		void run();

		static const int WIDTH;
		static const int HEIGHT;

	protected:
		void init();
		void mainLoop();
		void dispose();

	private:
		ModuleHandler modules;
	};
}
