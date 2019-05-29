#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class Instance;
	class Surface;

	class PhysicalDevice
	{
	public:
		PhysicalDevice();

		operator const VkPhysicalDevice&() const;
		const VkPhysicalDevice& getPhysicalDevice() const;

		void pick(const Instance& instance, const Surface& surface);

		const VkPhysicalDeviceMemoryProperties& getMemoryProperties() const;

	private:
		VkPhysicalDevice choosePhysicalDevice(const std::vector<VkPhysicalDevice>& devices, const VkSurfaceKHR& surface);
		bool isDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
		bool checkDeviceExtensionSupport(const VkPhysicalDevice& device);
		void logPhysicalDevice(const VkPhysicalDeviceProperties& physicalDeviceProperties, const std::vector<VkExtensionProperties>& extensionProperties);

	private:
		VkPhysicalDevice physicalDevice;
		VkPhysicalDeviceMemoryProperties memoryProperties;
	};
}
