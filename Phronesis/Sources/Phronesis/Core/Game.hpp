#pragma once

namespace Phronesis
{
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		void run();

	protected:
		void init();
		void mainLoop();
		void dispose();

	private:
		Renderer* renderer;
	};
}
