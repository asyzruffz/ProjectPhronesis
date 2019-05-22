
#include "StdAfx.hpp"
#include "Window.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Renderer.hpp"

using namespace Phronesis;

void Window::init(int width, int height, const char * title)
{
	glfwInit(); // initialize the glfw library
}

void Window::update()
{
}

std::vector<const char*> Window::getRequiredExtensions() const
{
	// GLFW built-in function returning the extension(s) required to 
	// interface with the window system
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
}
