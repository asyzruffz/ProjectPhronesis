#pragma once

#include <optional>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	struct QueueFamilyIndices
	{
		std::optional<unsigned int> graphicsFamily;
		std::optional<unsigned int> presentationFamily;
		bool isComplete();

		static QueueFamilyIndices find(VkPhysicalDevice device, VkSurfaceKHR surface);
	};
}
