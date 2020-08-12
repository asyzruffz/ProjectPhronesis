
#include "StdAfx.hpp"
#include "SFMLWindow.hpp"

#include "Phronesis/Core/Module.ext.hpp"
#include "Phronesis/Graphics/Renderer.hpp"

using namespace Phronesis;

void SFMLWindow::init(unsigned int width, unsigned int height, const char* title)
{
	window.create(sf::VideoMode(width, height), title);
}

void SFMLWindow::update()
{
	// Event processing
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Request for closing the window
		if (event.type == sf::Event::Closed)
		{
			Engine::Get()->stop();
			return;
		}
		else if (event.type == sf::Event::Resized)
		{
			triggerResize(event.size.width, event.size.height);
		}
	}
}

void SFMLWindow::dispose()
{
	window.close();
}

void SFMLWindow::handleMinimize()
{
	sf::Event event;
	sf::Vector2u size;
	while(size.x == 0 || size.y == 0)
	{	// when minimized, pause until the window is in the foreground
		size = window.getSize();
		window.waitEvent(event);
	}
}

sf::RenderWindow* SFMLWindow::getWindow()
{
	return &window;
}
/*
std::vector<const char*> SFMLWindow::getRequiredExtensions() const
{
	// SFML built-in function returning the extension(s) required to 
	// interface with the window system
	std::vector<const char*> requiredExtentions;
	if(sf::Vulkan::isAvailable())
	{
		requiredExtentions = sf::Vulkan::getGraphicsRequiredInstanceExtensions();
	}
	return requiredExtentions;
}

void SFMLWindow::createSurface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const
{
	if(!window.createVulkanSurface(instance, *surface, allocator))
	{
		Log::error("[SFML] Failed to create window surface");
	}
}
*/
void SFMLWindow::triggerResize(unsigned int width, unsigned int height)
{
	Module::getModule<Window>()->setSize(width, height);
	if(Module::hasModule<Renderer>())
	{
		Module::getModule<Renderer>()->requestResize();
	}
}
