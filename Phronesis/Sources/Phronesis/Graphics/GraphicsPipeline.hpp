#pragma once

#include <vector>

#include "Pipeline.hpp"

namespace Phronesis
{
	class LogicalDevice;
	class SwapChain;
	class Shader;
	class RenderPass;

	class GraphicsPipeline : public Pipeline
	{
	public:
		GraphicsPipeline();
		
		void create(const LogicalDevice& device, const SwapChain& swapChain, const std::vector<Shader>& shaders, const RenderPass& renderPass);
	
	};
}
