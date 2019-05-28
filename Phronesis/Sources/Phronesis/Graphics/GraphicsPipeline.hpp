#pragma once

#include "Pipeline.hpp"

namespace Phronesis
{
	class LogicalDevice;
	class SwapChain;
	class RenderPass;

	class GraphicsPipeline : public Pipeline
	{
	public:
		
		void create(const LogicalDevice& device, const SwapChain& swapChain, const VkPipelineShaderStageCreateInfo* shaderStages, const RenderPass& renderPass);

	};
}
