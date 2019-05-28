#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Phronesis
{
	class RenderUtils
	{
	public:
		static void checkVk(const VkResult &result);

	private:
		static std::string stringifyResultVk(const VkResult &result);
		static std::string stringifyMessageSeverity(const VkDebugUtilsMessageSeverityFlagBitsEXT &severity);
	};
}
