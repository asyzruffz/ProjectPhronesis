#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class PhysicalDevice;
	struct QueueFamilyIndices;

	class LogicalDevice
	{
	public:
		LogicalDevice();

		operator const VkDevice&() const;
		const VkDevice& getLogicalDevice() const;

		void create(const PhysicalDevice& physicalDevice, const QueueFamilyIndices& indices);
		void dispose();

		const VkQueue& getGraphicsQueue() const;
		const VkQueue& getPresentationQueue() const;

	private:
		VkDevice logicalDevice;

		VkQueue graphicsQueue;
		VkQueue presentationQueue;
	};
}
