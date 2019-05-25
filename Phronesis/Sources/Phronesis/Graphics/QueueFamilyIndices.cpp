
#include "StdAfx.hpp"
#include "QueueFamilyIndices.hpp"

#include <vulkan/vulkan.h>

using namespace Phronesis;

bool QueueFamilyIndices::isComplete()
{
	return graphicsFamily.has_value() && presentationFamily.has_value();
}

QueueFamilyIndices QueueFamilyIndices::find(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	QueueFamilyIndices indices;

	// retrieving the list of queue families
	unsigned int queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for(const auto& queueFamily : queueFamilies)
	{
		// find at least one queue family that supports VK_QUEUE_GRAPHICS_BIT
		if(queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}

		// also look for a queue family that has the capability of presenting to our window surface
		VkBool32 presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentationSupport);

		if(queueFamily.queueCount > 0 && presentationSupport)
		{
			indices.presentationFamily = i;
		}

		if(indices.isComplete())
		{
			break;
		}

		i++;
	}

	return indices;
}
