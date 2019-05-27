#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class SwapChain;
	class RenderPass;

	class FrameBuffers
	{
	public:
		FrameBuffers();

		const std::vector<VkFramebuffer>& getFrameBuffers() const;
		VkFramebuffer& operator[](const size_t i);
		const size_t size() const;

		void create(const LogicalDevice& device, const SwapChain& swapChain, const RenderPass& renderPass);
		void dispose(const LogicalDevice& device);

	private:
		std::vector<VkFramebuffer> frameBuffers;
	};
}
