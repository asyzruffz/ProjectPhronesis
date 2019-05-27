#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class SwapChain;

	class RenderPass
	{
	public:
		RenderPass();

		operator const VkRenderPass&() const;
		const VkRenderPass& getRenderPass() const;

		void create(const LogicalDevice& device, const SwapChain& swapChain);
		void dispose(const LogicalDevice& device);

	private:
		VkRenderPass renderPass;
	};
}
