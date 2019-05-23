
#include "StdAfx.hpp"
#include "Window.hpp"

#include <GLFW/glfw3.h>

#include "Phronesis/Core/Engine.hpp"
#include "Renderer.hpp"

using namespace Phronesis;

static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto windowModule = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	windowModule->triggerResize(width, height);
}

void Window::init(unsigned int width, unsigned int height, const char* title)
{
	size.x = width; size.y = height;

	glfwInit(); // initialize the glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // tell it to not create an OpenGL context
	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable window resize

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwSetWindowUserPointer(window, this); // store a reference to Renderer class with this window
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback); // callback for window resize
}

void Window::update()
{
	if(glfwWindowShouldClose(window))
	{
		Engine::Get()->stop();
		return;
	}

	glfwPollEvents();
}

void Phronesis::Window::dispose()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	//system("pause");
}

const Vector2ui& Window::getSize() const
{
	return size;
}

std::vector<const char*> Window::getRequiredExtensions() const
{
	// GLFW built-in function returning the extension(s) required to 
	// interface with the window system
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
}

VkResult Window::createSurface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const
{
	return glfwCreateWindowSurface(instance, window, allocator, surface);
}

void Window::triggerResize(unsigned int width, unsigned int height)
{
	size.x = width; size.y = height;
	getModule<Renderer>()->requestResize();
}

void Window::handleMinimize()
{
	int width = 0, height = 0;
	while(width == 0 || height == 0)
	{	// when minimized, pause until the window is in the foreground
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}
}
