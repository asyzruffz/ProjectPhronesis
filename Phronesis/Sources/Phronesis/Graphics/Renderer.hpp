#pragma once

#include <vulkan/vulkan.h>

#include <vector>

struct GLFWwindow;

namespace Phronesis
{
	class Renderer
	{
	public:
		void initWindow(int width, int height, const char* title);
		void initVulkan();
		void update();
		void disposeVulkan();
		void disposeWindow();

	private:
		GLFWwindow* window;
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		void createInstance();
		void setupDebugMessenger();
		void pickPhysicalDevice();
		std::vector<const char*> getRequiredExtensions();
	};
}
