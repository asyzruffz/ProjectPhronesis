#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Phronesis
{
	class RenderUtils
	{
	public:
		static void checkVk(const VkResult &result);

		// Device related
		static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

		// Swap chain related
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);

		// Shader related
		static VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

	private:
		static std::string stringifyResultVk(const VkResult &result);
		static std::string stringifyMessageSeverity(const VkDebugUtilsMessageSeverityFlagBitsEXT &severity);

		static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}
