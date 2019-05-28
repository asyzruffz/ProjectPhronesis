#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;

	class CommandPool
	{
	public:
		CommandPool();

		operator const VkCommandPool&() const;
		const VkCommandPool& getCommandPool() const;

		void create(const LogicalDevice& device);
		void dispose(const LogicalDevice& device);

	private:
		VkCommandPool commandPool;
	};
}
