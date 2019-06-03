
#include "StdAfx.hpp"
#include "Pipeline.hpp"

#include "LogicalDevice.hpp"
#include "Shader.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

Pipeline::Pipeline() :
	pipeline(VK_NULL_HANDLE),
	pipelineLayout(VK_NULL_HANDLE),
	pipelineBindPoint(VK_PIPELINE_BIND_POINT_GRAPHICS),
	descriptorSetLayout(VK_NULL_HANDLE)
{
}

void Pipeline::dispose(const LogicalDevice& device)
{
	vkDestroyPipeline(device, pipeline, nullptr);
	vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
	vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
}

void Pipeline::bind(const VkCommandBuffer& commandBuffer) const
{
	vkCmdBindPipeline(commandBuffer, getPipelineBindPoint(), getPipeline());
}

const VkPipeline& Pipeline::getPipeline() const
{
	return pipeline;
}

const VkPipelineLayout& Pipeline::getPipelineLayout() const
{
	return pipelineLayout;
}

const VkPipelineBindPoint& Pipeline::getPipelineBindPoint() const
{
	return pipelineBindPoint;
}

void Pipeline::createDescriptorSetLayout(const LogicalDevice& device, const std::vector<Shader>& shaders)
{
	auto& descriptorSetLayouts = shaders[0].getDescriptorSetLayouts();

	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	layoutInfo.pBindings = descriptorSetLayouts.data();

	VkResult result = vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create descriptor set layout");
		RenderUtils::checkVk(result);
	}
}

void Pipeline::createPipelineLayout(const LogicalDevice& device)
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
	pipelineLayoutInfo.pushConstantRangeCount = 0;

	VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create pipeline layout");
		RenderUtils::checkVk(result);
	}
}
