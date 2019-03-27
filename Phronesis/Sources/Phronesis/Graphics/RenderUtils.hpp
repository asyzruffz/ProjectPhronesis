#pragma once

#include <string>
#include <vector>

#include "QueueFamilyIndices.hpp"
#include "SwapChainSupportDetails.hpp"

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class RenderUtils
	{
	public:
		// Validation layer related
		static void checkVk(const VkResult &result);
		static bool checkValidationLayerSupport();

		static VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		static void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		// Device related
		static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

		// Swap chain related
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		// Lists to configure
		static const std::vector<const char*> validationLayers;
		static const std::vector<const char*> deviceExtensions;

	private:
		static std::string stringifyResultVk(const VkResult &result);
		static std::string stringifyMessageSeverity(const VkDebugUtilsMessageSeverityFlagBitsEXT &severity);

		static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}
