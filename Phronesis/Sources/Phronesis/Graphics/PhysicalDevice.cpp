
#include "StdAfx.hpp"
#include "PhysicalDevice.hpp"

#include "Instance.hpp"
#include "Surface.hpp"
#include "QueueFamilyIndices.hpp"

using namespace Phronesis;

PhysicalDevice::PhysicalDevice() :
	physicalDevice(VK_NULL_HANDLE),
	memoryProperties({})
{
}

PhysicalDevice::operator const VkPhysicalDevice&() const
{
	return physicalDevice;
}

const VkPhysicalDevice& PhysicalDevice::getPhysicalDevice() const
{
	return physicalDevice;
}

void PhysicalDevice::pick(const Instance& instance, const Surface& surface)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if(deviceCount == 0)
	{
		throw std::runtime_error("[Vulkan] Failed to find GPUs with Vulkan support");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	physicalDevice = choosePhysicalDevice(devices, surface);

	if(physicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("[Vulkan] Failed to find a suitable GPU");
	}

	// query info about the available types of memory
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

	// print info about chosen GPU
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

	unsigned int extensionPropertyCount;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionPropertyCount, nullptr);
	std::vector<VkExtensionProperties> extensionProperties(extensionPropertyCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionPropertyCount, extensionProperties.data());
	
	logPhysicalDevice(deviceProperties, extensionProperties);
}

const VkPhysicalDeviceMemoryProperties& PhysicalDevice::getMemoryProperties() const
{
	return memoryProperties;
}

VkPhysicalDevice PhysicalDevice::choosePhysicalDevice(const std::vector<VkPhysicalDevice>& devices, const VkSurfaceKHR& surface)
{
	for(const auto& device : devices)
	{
		if(isDeviceSuitable(device, surface))
		{
			return device;
		}
	}

	return VK_NULL_HANDLE;
}

bool PhysicalDevice::isDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
{
	// check for required features if neccessary

	// check which queue families are supported by the device
	QueueFamilyIndices indices = QueueFamilyIndices::find(device, surface);

	// check if the device extension(s) is supported
	bool extensionsSupported = checkDeviceExtensionSupport(device);

	// verify that swap chain support is adequate
	bool swapChainAdequate = false;
	if(extensionsSupported)
	{
		auto swapChainSupport = Surface::querySwapChainSupport(device, surface);
		swapChainAdequate = !swapChainSupport.first.empty() && !swapChainSupport.second.empty();
	}

	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool PhysicalDevice::checkDeviceExtensionSupport(const VkPhysicalDevice & device)
{
	// enumerate the available extensions
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	// check if all of the required extensions are amongst them
	std::set<std::string> requiredExtensions(Instance::deviceExtensions.begin(), Instance::deviceExtensions.end());

	for(const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

void PhysicalDevice::logPhysicalDevice(const VkPhysicalDeviceProperties& physicalDeviceProperties, const std::vector<VkExtensionProperties>& extensionProperties)
{
	std::stringstream stream;

	switch(static_cast<int>(physicalDeviceProperties.deviceType))
	{
		case 1:
			stream << "Integrated";
			break;
		case 2:
			stream << "Discrete";
			break;
		case 3:
			stream << "Virtual";
			break;
		case 4:
			stream << "CPU";
			break;
		default:
			stream << "Other " << physicalDeviceProperties.deviceType;
	}

	stream << " GPU: " << physicalDeviceProperties.deviceID << std::endl;

	stream << "\t";
	switch(physicalDeviceProperties.vendorID)
	{
		case 0x8086:
			stream << "Intel";
			break;
		case 0x10DE:
			stream << "Nvidia";
			break;
		case 0x1002:
			stream << "AMD";
			break;
		default:
			stream << physicalDeviceProperties.vendorID;
	}

	stream << " " << physicalDeviceProperties.deviceName << std::endl;

	unsigned int supportedVersion[] = { 
		VK_VERSION_MAJOR(physicalDeviceProperties.apiVersion), 
		VK_VERSION_MINOR(physicalDeviceProperties.apiVersion),
		VK_VERSION_PATCH(physicalDeviceProperties.apiVersion) };
	stream << "\tAPI Version: " << supportedVersion[0] << "." << supportedVersion[1] << "." << supportedVersion[2] << std::endl;

	stream << "\tExtensions: " << extensionProperties.size() << std::endl;
	/*for(const auto &extension : extensionProperties)
	{
		stream << "\t\t" << extension.extensionName << "\n";
	}
	stream << std::endl;*/

	Log::info(stream.str());
}
