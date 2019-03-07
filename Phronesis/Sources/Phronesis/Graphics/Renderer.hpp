#pragma once

#include <string>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		static void checkVk(const VkResult &result);
		static std::string stringifyResultVk(const VkResult &result);
	};
}
