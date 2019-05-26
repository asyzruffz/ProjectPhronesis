#pragma once

#include <vulkan/vulkan.h>

#include "QueueFamilyIndices.hpp"

namespace Phronesis
{
	class PhysicalDevice;
	class Surface;
	struct QueueFamilyIndices;

	class LogicalDevice
	{
	public:
		LogicalDevice();

		operator const VkDevice&() const;
		const VkDevice& getLogicalDevice() const;

		void create(const PhysicalDevice& physicalDevice, const Surface& surface);
		void dispose();

		const unsigned int& getGraphicsFamily() const;
		const unsigned int& getPresentationFamily() const;

		const VkQueue& getGraphicsQueue() const;
		const VkQueue& getPresentationQueue() const;

	private:
		void findQueueFamilies(const PhysicalDevice& device, const Surface& surface);

	private:
		VkDevice logicalDevice;

		QueueFamilyIndices queueIndices;

		VkQueue graphicsQueue;
		VkQueue presentationQueue;
	};
}
