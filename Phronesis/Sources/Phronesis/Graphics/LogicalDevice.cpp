
#include "StdAfx.hpp"
#include "LogicalDevice.hpp"

using namespace Phronesis;

#include "Instance.hpp"
#include "QueueFamilyIndices.hpp"
#include "PhysicalDevice.hpp"
#include "RenderUtils.hpp"

LogicalDevice::LogicalDevice() :
	logicalDevice(VK_NULL_HANDLE)
{
}

LogicalDevice::operator const VkDevice&() const
{
	return logicalDevice;
}

const VkDevice& LogicalDevice::getLogicalDevice() const
{
	return logicalDevice;
}

void LogicalDevice::create(const PhysicalDevice& physicalDevice, const QueueFamilyIndices& indices)
{
	// make sure the queue families are not redundant while making different queues
	std::set<unsigned int> uniqueQueueFamilies = {
		indices.graphicsFamily.value(),
		indices.presentationFamily.value()
	};

	// vector to store the createinfos for each queue
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

	float queuePriority = 1.0f; // between 0.0 and 1.0
	for(uint32_t queueFamily : uniqueQueueFamilies)
	{
		// specifying details for logical device creation
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1; // the number of queues we want for a single queue family
		queueCreateInfo.pQueuePriorities = &queuePriority;

		queueCreateInfos.push_back(queueCreateInfo);
	}

	// specify is the set of device features that we'll be using.
	// features that needed to be queried support for with vkGetPhysicalDeviceFeatures 
	// in RenderUtils::isDeviceSuitable()
	VkPhysicalDeviceFeatures deviceFeatures = {};

	// creating the logical device
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(Instance::deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = Instance::deviceExtensions.data();
	if(Instance::enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(Instance::validationLayers.size());
		createInfo.ppEnabledLayerNames = Instance::validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create logical device");
		RenderUtils::checkVk(result);
	}

	// the queues are automatically created along with the logical device,
	// but we need to have a handle to interface with the graphics and presentation queue
	vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(logicalDevice, indices.presentationFamily.value(), 0, &presentationQueue);
}

void LogicalDevice::dispose()
{
	vkDestroyDevice(logicalDevice, nullptr);
}

const VkQueue& LogicalDevice::getGraphicsQueue() const
{
	return graphicsQueue;
}

const VkQueue& LogicalDevice::getPresentationQueue() const
{
	return presentationQueue;
}
