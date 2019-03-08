#pragma once

#include <vector>

struct GLFWwindow;

namespace Phronesis
{
	struct RenderInstance;

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
		void dispose();

	private:
		GLFWwindow* window;
		RenderInstance* instance;

		void createInstance();
		std::vector<const char*> getRequiredExtensions();
		bool checkValidationLayerSupport();
	};
}
