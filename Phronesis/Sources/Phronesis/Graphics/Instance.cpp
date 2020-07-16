
#include "StdAfx.hpp"
#include "Instance.hpp"

#include "Phronesis/Core/Engine.hpp"
#include "Phronesis/Core/Game.hpp"
#include "RenderUtils.hpp"
#include "Window.hpp"

using namespace Phronesis;

#ifdef NDEBUG // means "not debug"
const bool Instance::enableValidationLayers = false;
#else
const bool Instance::enableValidationLayers = true;
#endif

// Requested standard diagnostics layers provided by the Vulkan SDK
const std::vector<const char*> Instance::validationLayers = {
	//"VK_LAYER_LUNARG_standard_validation" // For old vulkan sdk version
	"VK_LAYER_KHRONOS_validation"
};

// Requested device extension for image presentation to surface
const std::vector<const char*> Instance::deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

Instance::Instance() :
	instance(VK_NULL_HANDLE),
	debugMessenger(VK_NULL_HANDLE)
{
	createInstance();
	createDebugMessenger();
}


Instance::~Instance()
{
	if(enableValidationLayers)
	{	// destroy debug messenger resposible for validation
		destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}

	// destroy Vulkan instance
	vkDestroyInstance(instance, nullptr);
}

Instance::operator const VkInstance&() const
{
	return instance;
}

const VkInstance& Instance::getInstance() const
{
	return instance;
}

VkResult Instance::createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if(func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void Instance::destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if(func != nullptr)
	{
		func(instance, debugMessenger, pAllocator);
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL Instance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
	switch(messageSeverity)
	{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			Log::info("[Vulkan] {}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		default:
			Log::error("[Vulkan] {}", pCallbackData->pMessage);
			break;
	}

	//Log::info("[Vulkan] [{}] {}", stringifyMessageSeverity(messageSeverity), pCallbackData->pMessage);
	return VK_FALSE;
}

bool Instance::checkValidationLayerSupport()
{
	// list all of the available layers
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	// log the validation layers
#ifndef NDEBUG
	/*
	std::cout << std::endl;
	Log::debug("[Vulkan] Required validation layers:");
	for(const char* layerName : validationLayers)
	{
		std::cout << "\t" << layerName << std::endl;
	}

	std::cout << std::endl;
	Log::debug("[Vulkan] Available validation layers:");
	for(const auto& layerProperties : availableLayers)
	{
		std::cout << "\t" << layerProperties.layerName << std::endl;
	}
	*/
#endif

	// check if all of the layers in validationLayers exist in the availableLayers list
	for(const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for(const auto& layerProperties : availableLayers)
		{
			if(strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if(!layerFound)
		{
			return false;
		}
	}

	return true;
}

std::vector<const char*> Instance::getRequiredExtensions()
{
	auto extensions = Engine::Get()->getGame().getModule<Window>()->getRequiredExtensions();

	// extension to set up a debug messenger with a callback
	if(enableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	// log the extensions
#ifndef NDEBUG
	/*
	// get a list of available extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensionsAvailable(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsAvailable.data());

	std::string ext = "";
	ext = "[Vulkan] Required extensions:";
	for(const auto& extension : extensions)
	{
		ext += "\n\t" + std::string(extension);
	}

	std::cout << std::endl;
	Log::debug(ext);
	std::cout << std::endl;

	ext = "[Vulkan] Available extensions:";
	for(const auto& extension : extensionsAvailable)
	{
		ext += "\n\t" + std::string(extension.extensionName);
	}

	Log::debug(ext);
	std::cout << std::endl;
	*/
#endif

	return extensions;
}

void Instance::createInstance()
{
	if(enableValidationLayers && !checkValidationLayerSupport())
	{
		throw std::runtime_error("[Vulkan] Validation layers requested, but not available");
	}

	// information about our application
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Game";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Phronesis";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	auto extensions = getRequiredExtensions();

	// parameters for creating a Vulkan instance (not optional),
	// tells the Vulkan driver which global extensions and
	// validation layers we want to use
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
	if(enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create instance");
		RenderUtils::checkVk(result);
	}
}

void Instance::createDebugMessenger()
{
	if(!enableValidationLayers) return;

	// function parameters for creating debug messenger,
	// detailing the messages type and severity that will run callback 
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | /*VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |*/ VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = Instance::debugCallback;
	createInfo.pUserData = nullptr; // Optional

	VkResult result = createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to set up debug messenger");
		RenderUtils::checkVk(result);
	}
}
