#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentationModes;

		static SwapChainSupportDetails query(VkPhysicalDevice device, VkSurfaceKHR surface);
	};
}
