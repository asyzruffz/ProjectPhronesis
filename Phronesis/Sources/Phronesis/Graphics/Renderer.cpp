
#include "Renderer.hpp"

#include <iostream>
#include <stdexcept>

#include "Phronesis/Graphics/RenderUtils.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace Phronesis;


#ifdef NDEBUG // means "not debug"
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

void Renderer::initWindow(int width, int height, const char* title)
{
	glfwInit(); // initialize the glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // tell it to not create an OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable window resize

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void Renderer::initVulkan()
{
	createInstance();
	setupDebugMessenger();
	pickPhysicalDevice();
	createLogicalDevice();
}

void Renderer::update()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void Renderer::disposeVulkan()
{
	vkDestroyDevice(device, nullptr);
	if (enableValidationLayers) 
	{	// destroy debug messenger resposible for validation
		RenderUtils::destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}
	vkDestroyInstance(instance, nullptr); // destroy Vulkan instance
}

void Renderer::disposeWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	//system("pause");
}

void Renderer::createInstance()
{
	if (enableValidationLayers && !RenderUtils::checkValidationLayerSupport()) {
		throw std::runtime_error("Vulkan error: Validation layers requested, but not available!");
	}

	// some information about our application
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Game";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Phronesis";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	auto extensions = getRequiredExtensions();

	// log the extensions
#ifndef NDEBUG
	// get a list of available extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensionsAvailable(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsAvailable.data());

	std::cout << "Vulkan info: Required extensions:" << std::endl;
	for (const auto& extension : extensions) {
		std::cout << "\t" << extension << std::endl;
	}

	std::cout << "Vulkan info: Available extensions:" << std::endl;
	for (const auto& extension : extensionsAvailable) {
		std::cout << "\t" << extension.extensionName << std::endl;
	}
#endif

	// function parameters for creating a Vulkan instance (not optional),
	// tells the Vulkan driver which global extensions and
	// validation layers we want to use
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(RenderUtils::validationLayers.size());
		createInfo.ppEnabledLayerNames = RenderUtils::validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	RenderUtils::checkVk(result);
}

void Renderer::setupDebugMessenger()
{
	if (!enableValidationLayers) return;

	// function parameters for creating debug messenger,
	// detailing the messages type and severity that will run callback 
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = RenderUtils::debugCallback;
	createInfo.pUserData = nullptr; // Optional

	VkResult result = RenderUtils::createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
	if (result != VK_SUCCESS) {
		std::cerr << "Vulkan error: Failed to set up debug messenger" << std::endl;
		RenderUtils::checkVk(result);
	}
}

void Renderer::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("Vulkan error: Failed to find GPUs with Vulkan support");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (RenderUtils::isDeviceSuitable(device)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("Vulkan error: Failed to find a suitable GPU");
	}
}

void Renderer::createLogicalDevice()
{
	QueueFamilyIndices indices = RenderUtils::findQueueFamilies(physicalDevice);

	// The currently available drivers will only allow you to create
	// a small number of queues for each queue family and you don't really
	// need more than one. That's because you can create all of the command buffers 
	// on multiple threads and then submit them all at once on the main thread 
	// with a single low-overhead call.

	// specifying details for logical device creation
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1; // the number of queues we want for a single queue family

	float queuePriority = 1.0f; // between 0.0 and 1.0
	queueCreateInfo.pQueuePriorities = &queuePriority;

	// specify is the set of device features that we'll be using.
	// features that needed to be queried support for with vkGetPhysicalDeviceFeatures 
	// in RenderUtils::isDeviceSuitable()
	VkPhysicalDeviceFeatures deviceFeatures = {};

	// creating the logical device
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0; // TODO: enable some extensions
	if(enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(RenderUtils::validationLayers.size());
		createInfo.ppEnabledLayerNames = RenderUtils::validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
	if(result != VK_SUCCESS)
	{
		std::cerr << "Vulkan error: Failed to create logical device" << std::endl;
		RenderUtils::checkVk(result);
	}

	// the queues are automatically created along with the logical device,
	// but we need to have a handle to interface with the graphics queue
	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

std::vector<const char*> Renderer::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	// GLFW built-in function returning the extension(s) required to 
	// interface with the window system
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	// extension to set up a debug messenger with a callback
	if (enableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}
