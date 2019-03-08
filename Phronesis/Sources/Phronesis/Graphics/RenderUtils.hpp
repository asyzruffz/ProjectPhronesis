#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class RenderUtils
	{
	public:
		static void checkVk(const VkResult &result);
		static std::string stringifyResultVk(const VkResult &result);
		static bool checkValidationLayerSupport();

		static VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		static void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		static const std::vector<const char*> validationLayers;

		static bool isDeviceSuitable(VkPhysicalDevice device);
	};
}
