
#include "StdAfx.hpp"
#include "LogicalDevice.hpp"

using namespace Phronesis;

#include "Instance.hpp"
#include "PhysicalDevice.hpp"
#include "Surface.hpp"
#include "QueueFamilyIndices.hpp"
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

void LogicalDevice::create(const PhysicalDevice& physicalDevice, const Surface& surface)
{
	findQueueFamilies(physicalDevice, surface);

	// make sure the queue families are not redundant while making different queues
	std::set<unsigned int> uniqueQueueFamilies = {
		getGraphicsFamily(),
		getPresentationFamily(),
		getComputeFamily(),
		getTransferFamily()
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
	vkGetDeviceQueue(logicalDevice, getGraphicsFamily(), 0, &graphicsQueue);
	vkGetDeviceQueue(logicalDevice, getPresentationFamily(), 0, &presentationQueue);
	vkGetDeviceQueue(logicalDevice, getComputeFamily(), 0, &computeQueue);
	vkGetDeviceQueue(logicalDevice, getTransferFamily(), 0, &transferQueue);
}

void LogicalDevice::dispose()
{
	vkDestroyDevice(logicalDevice, nullptr);
}

const unsigned int& LogicalDevice::getGraphicsFamily() const
{
	return queueIndices.graphicsFamily.value();
}

const unsigned int& LogicalDevice::getPresentationFamily() const
{
	return queueIndices.presentationFamily.value();
}

const unsigned int& LogicalDevice::getComputeFamily() const
{
	return queueIndices.computeFamily.value();
}

const unsigned int& LogicalDevice::getTransferFamily() const
{
	return queueIndices.transferFamily.value();
}

const VkQueue& LogicalDevice::getGraphicsQueue() const
{
	return graphicsQueue;
}

const VkQueue& LogicalDevice::getPresentationQueue() const
{
	return presentationQueue;
}

const VkQueue& LogicalDevice::getComputeQueue() const
{
	return computeQueue;
}

const VkQueue& LogicalDevice::getTransferQueue() const
{
	return transferQueue;
}

void LogicalDevice::findQueueFamilies(const PhysicalDevice& device, const Surface& surface)
{
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
			queueIndices.graphicsFamily = i;
		}

		// also look for a queue family that has the capability of presenting to our window surface
		VkBool32 presentationSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentationSupport);

		if(queueFamily.queueCount > 0 && presentationSupport)
		{
			queueIndices.presentationFamily = i;
		}

		// check for compute support
		if(queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
		{
			queueIndices.computeFamily = i;
		}

		// check for transfer support
		if(queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
		{
			queueIndices.transferFamily = i;
		}

		if(queueIndices.isComplete())
		{
			break;
		}

		i++;
	}
}
