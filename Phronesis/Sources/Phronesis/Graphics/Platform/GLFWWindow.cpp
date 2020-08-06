
#include "StdAfx.hpp"
#include "GLFWWindow.hpp"

#include <GLFW/glfw3.h>

#include "Phronesis/Core/Module.ext.hpp"
#include "Phronesis/Graphics/Renderer.hpp"
#include "Phronesis/Graphics/RenderUtils.hpp"

using namespace Phronesis;

static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto windowModule = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
	windowModule->triggerResize(width, height);
}

void GLFWWindow::init(unsigned int width, unsigned int height, const char* title)
{
	glfwInit(); // initialize the glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // tell it to not create an OpenGL context
	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable window resize

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwSetWindowUserPointer(window, this); // store a reference to Renderer class with this window
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback); // callback for window resize
}

void GLFWWindow::update()
{
	if(glfwWindowShouldClose(window))
	{
		Engine::Get()->stop();
		return;
	}

	glfwPollEvents();
}

void GLFWWindow::dispose()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void GLFWWindow::handleMinimize()
{
	int width = 0, height = 0;
	while(width == 0 || height == 0)
	{	// when minimized, pause until the window is in the foreground
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}
}

std::vector<const char*> GLFWWindow::getRequiredExtensions() const
{
	// GLFW built-in function returning the extension(s) required to 
	// interface with the window system
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
}

void GLFWWindow::createSurface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const
{
	VkResult result = glfwCreateWindowSurface(instance, window, allocator, surface);
	if(result != VK_SUCCESS)
	{
		Log::error("[GLFW] Failed to create window surface");
		RenderUtils::checkVk(result);
	}
}

void GLFWWindow::triggerResize(unsigned int width, unsigned int height)
{
	Module::getModule<Window>()->setSize(width, height);
	Module::getModule<Renderer>()->requestResize();
}
