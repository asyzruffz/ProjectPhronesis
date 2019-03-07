
#include "Game.hpp"

#include <iostream>
#include <vector>

#include "Phronesis/Graphics/RenderInstance.hpp"
#include "Phronesis/Graphics/Renderer.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace Phronesis;

const int WIDTH = 800;
const int HEIGHT = 600;

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
	// some information about our application
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Test Game";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Phronesis";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	// GLFW built-in function returning the extension(s)
	// required to interface with the window system
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	
	// ------ bonus ------
	std::cout << "required extensions:" << std::endl;
	for (uint32_t i = 0; i < glfwExtensionCount; i++) {
		std::cout << "\t" << glfwExtensions[i] << std::endl;
	}

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "available extensions:" << std::endl;
	for (const auto& extension : extensions) {
		std::cout << "\t" << extension.extensionName << std::endl;
	}
	// ------ bonus ------

	// function parameters for creating a Vulkan instance (not optional),
	// tells the Vulkan driver which global extensions
	// and validation layers we want to use
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0; // the global validation layers to enable

	instance = new RenderInstance;
	VkResult result = vkCreateInstance(&createInfo, nullptr, &(instance->data));
	Renderer::checkVk(result);
}
