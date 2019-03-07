#pragma once

struct GLFWwindow;

namespace Phronesis
{
	class Game
	{
	public:
		Game();
		virtual ~Game() = default;

		void run();

	protected:
		void initWindow();
		void initVulkan();
		void mainLoop();
		void cleanup();

	private:
		GLFWwindow* window;
	};
}
