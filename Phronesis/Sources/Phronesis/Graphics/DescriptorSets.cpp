
#include "StdAfx.hpp"
#include "DescriptorSets.hpp"

#include "LogicalDevice.hpp"
#include "Pipeline.hpp"
#include "UniformBuffer.hpp"
#include "UniformBufferObject.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

const std::vector<VkDescriptorSet>& DescriptorSets::getDescriptorSets() const
{
	return descriptorSets;
}

VkDescriptorSet& DescriptorSets::operator[](const size_t i)
{
	return descriptorSets[i];
}

const size_t DescriptorSets::size() const
{
	return descriptorSets.size();
}

void DescriptorSets::allocate(const LogicalDevice& device, const Pipeline& pipeline, unsigned int count)
{
	std::vector<VkDescriptorSetLayout> layouts(count, pipeline.getDescriptorSetLayout());

	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = pipeline.getDescriptorPool();
	allocInfo.pSetLayouts = layouts.data();
	allocInfo.descriptorSetCount = count;

	descriptorSets.resize(count);
	VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data());
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to allocate descriptor sets");
		RenderUtils::checkVk(result);
	}
}

void DescriptorSets::configureDescriptors(const LogicalDevice& device, const std::vector<UniformBuffer>& uniformBuffers)
{
	for(size_t i = 0; i < descriptorSets.size(); i++)
	{
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;

		vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
	}
}

