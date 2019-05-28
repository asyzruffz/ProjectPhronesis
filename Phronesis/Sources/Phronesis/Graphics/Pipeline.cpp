
#include "StdAfx.hpp"
#include "Pipeline.hpp"

#include "LogicalDevice.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

Pipeline::Pipeline() :
	pipeline(VK_NULL_HANDLE),
	pipelineLayout(VK_NULL_HANDLE),
	pipelineBindPoint(VK_PIPELINE_BIND_POINT_GRAPHICS)
{
}

void Pipeline::dispose(const LogicalDevice& device)
{
	vkDestroyPipeline(device, pipeline, nullptr);
	vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
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

void Pipeline::createPipelineLayout(const LogicalDevice& device)
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pushConstantRangeCount = 0;

	VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create pipeline layout");
		RenderUtils::checkVk(result);
	}
}
