
#include "Game.hpp"

#include <iostream>
#include <cstring> // for strcmp
#include <stdexcept>

#include "Phronesis/Graphics/RenderInstance.hpp"
#include "Phronesis/Graphics/RenderUtils.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace Phronesis;

const int WIDTH = 800;
const int HEIGHT = 600;

// request standard diagnostics layers provided by the Vulkan SDK
const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

#ifdef NDEBUG // means "not debug"
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

Game::Game()
{
}

void Game::run()
{
	initWindow();
	initVulkan();
	mainLoop();
	dispose();
}

void Game::initWindow()
{
	glfwInit(); // initialize the glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // tell it to not create an OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable window resize

	window = glfwCreateWindow(WIDTH, HEIGHT, "Phronesis - Test Game (Vulkan)", nullptr, nullptr);
}

void Game::initVulkan()
{
	createInstance();
}

void Game::mainLoop()
{
	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
	}
}

void Game::dispose()
{
	vkDestroyInstance(instance->data, nullptr);
	delete instance;

	glfwDestroyWindow(window);

	glfwTerminate();
}

void Game::createInstance()
{
	if (enableValidationLayers && !checkValidationLayerSupport()) {
		throw std::runtime_error("Vulkan error: Validation layers requested, but not available!");
	}

	// some information about our application
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Test Game";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Phronesis";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	auto extensions = getRequiredExtensions();
	
	// log the extensions
#ifndef NDEBUG
	std::cout << "Vulkan info: Required extensions:" << std::endl;
	for (const auto& extension : extensions) {
		std::cout << "\t" << extension << std::endl;
	}

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensionsA(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsA.data());

	std::cout << "Vulkan info: Available extensions:" << std::endl;
	for (const auto& extension : extensionsA) {
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
	createInfo.enabledLayerCount = 0; // the global validation layers to enable

	instance = new RenderInstance;
	VkResult result = vkCreateInstance(&createInfo, nullptr, &(instance->data));
	RenderUtils::checkVk(result);
}

std::vector<const char*> Game::getRequiredExtensions()
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

bool Game::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	// list all of the available layers
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	// check if all of the layers in validationLayers exist in the availableLayers list
	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}
