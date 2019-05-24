#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class Instance;

	class PhysicalDevice
	{
	public:
		PhysicalDevice();
		~PhysicalDevice();

		operator const VkPhysicalDevice&() const;
		const VkPhysicalDevice& getPhysicalDevice() const;

		void pick(const Instance* instance, VkSurfaceKHR surface);

	private:
		VkPhysicalDevice choosePhysicalDevice(const std::vector<VkPhysicalDevice>& devices, VkSurfaceKHR surface);
		void logPhysicalDevice(const VkPhysicalDeviceProperties& physicalDeviceProperties, const std::vector<VkExtensionProperties>& extensionProperties);

	private:
		VkPhysicalDevice physicalDevice;
	};
}
