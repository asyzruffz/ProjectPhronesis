#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class Shader;

	class Pipeline
	{
	public:
		Pipeline();
		virtual ~Pipeline() = default;

		virtual void dispose(const LogicalDevice& device);

		void bind(const VkCommandBuffer& commandBuffer) const;

		const VkPipeline& getPipeline() const;
		const VkPipelineLayout& getPipelineLayout() const;
		const VkPipelineBindPoint& getPipelineBindPoint() const;

	protected:
		virtual void createDescriptorSetLayout(const LogicalDevice& device, const std::vector<Shader>& shaders);
		virtual void createPipelineLayout(const LogicalDevice& device);

	protected:
		VkPipeline pipeline;
		VkPipelineLayout pipelineLayout;
		VkPipelineBindPoint pipelineBindPoint;
		VkDescriptorSetLayout descriptorSetLayout;
	};
}
