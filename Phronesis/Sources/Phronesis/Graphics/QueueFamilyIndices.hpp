#pragma once

#include <optional>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	struct QueueFamilyIndices
	{
		std::optional<unsigned int> graphicsFamily;
		std::optional<unsigned int> presentationFamily;
		std::optional<unsigned int> computeFamily;
		std::optional<unsigned int> transferFamily;
		bool isComplete();

		static QueueFamilyIndices find(VkPhysicalDevice device, VkSurfaceKHR surface);
	};
}
