
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Game.hpp"
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
	cleanup();
}

void Game::initWindow()
{
	glfwInit(); // initialize the glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // tell it to not create an OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable window resize

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Game::initVulkan()
{
}

void Game::mainLoop()
{
	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
	}
}

void Game::cleanup()
{
	glfwDestroyWindow(window);

	glfwTerminate();
}
