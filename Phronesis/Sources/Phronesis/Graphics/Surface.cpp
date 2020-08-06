
#include "StdAfx.hpp"
#include "Surface.hpp"

#include "Phronesis/Core.hpp"
#include "Platform/GLFWWindow.hpp"
#include "Instance.hpp"
#include "PhysicalDevice.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

Surface::Surface(VkSurfaceKHR surface) :
	surface(surface)
{
}

Surface::operator const VkSurfaceKHR&() const
{
	return surface;
}

const VkSurfaceKHR& Surface::getSurface() const
{
	return surface;
}

void Surface::create(const Instance& instance)
{
	auto windowmodule = static_cast<GLFWWindow*>(Module::getModule<Window>()->getImpl());
	windowmodule->createSurface(instance, nullptr, &surface);
}

void Surface::dispose(const Instance& instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}

void Surface::acquireProperties(const PhysicalDevice& device)
{
	// query the basic surface capabilities
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities);

	// query the supported surface formats
	unsigned int formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
	if(formatCount != 0)
	{
		formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formats.data());
	}

	// query the supported presentation modes
	unsigned int presentationModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentationModeCount, nullptr);
	if(presentationModeCount != 0)
	{
		presentationModes.resize(presentationModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentationModeCount, presentationModes.data());
	}
}

const VkSurfaceCapabilitiesKHR& Surface::getCapabilities() const
{
	return capabilities;
}

const std::vector<VkSurfaceFormatKHR>& Surface::getFormats() const
{
	return formats;
}

const std::vector<VkPresentModeKHR>& Surface::getPresentationModes() const
{
	return presentationModes;
}

std::pair<std::vector<VkSurfaceFormatKHR>, std::vector<VkPresentModeKHR>> Surface::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR _surface)
{
	std::vector<VkSurfaceFormatKHR> _formats;
	std::vector<VkPresentModeKHR> _presentationModes;

	// query the supported surface formats
	unsigned int formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, nullptr);
	if(formatCount != 0)
	{
		_formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, _surface, &formatCount, _formats.data());
	}

	// query the supported presentation modes
	unsigned int presentationModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentationModeCount, nullptr);
	if(presentationModeCount != 0)
	{
		_presentationModes.resize(presentationModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, _surface, &presentationModeCount, _presentationModes.data());
	}

	return { _formats, _presentationModes };
}
