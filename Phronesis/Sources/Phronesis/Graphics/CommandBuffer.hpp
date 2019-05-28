#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class CommandPool;

	class CommandBuffer
	{
	public:
		CommandBuffer();

		operator const VkCommandBuffer&() const;
		const VkCommandBuffer& getCommandBuffer() const;

		void allocate(const LogicalDevice& device, const CommandPool& commandPool);
		void free(const LogicalDevice& device, const CommandPool& commandPool);

		void begin();
		void end();

		void submit(const VkQueue& queue, const VkSemaphore& waitSemaphore = VK_NULL_HANDLE, const VkSemaphore& signalSemaphore = VK_NULL_HANDLE, VkFence fence = VK_NULL_HANDLE);

	private:
		VkCommandBuffer commandBuffer;

		bool running;
	};
}
