#pragma once

#include <string>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class RenderUtils
	{
	public:
		static void checkVk(const VkResult &result);
		static std::string stringifyResultVk(const VkResult &result);
	};
}
