#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class Instance
	{
	public:
		Instance();
		~Instance();

		operator const VkInstance&() const;
		const VkInstance& getInstance() const;

		static const bool enableValidationLayers;
		static const std::vector<const char*> validationLayers;
		static const std::vector<const char*> deviceExtensions;

	private:
		static VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		static void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();

		void createInstance();
		void createDebugMessenger();

	private:
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
	};
}
