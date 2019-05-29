
#include "StdAfx.hpp"
#include "CommandBuffer.hpp"

#include "LogicalDevice.hpp"
#include "CommandPool.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

CommandBuffer::CommandBuffer() :
	commandBuffer(VK_NULL_HANDLE),
	running(false)
{
}

CommandBuffer::operator const VkCommandBuffer&() const
{
	return commandBuffer;
}

const VkCommandBuffer& CommandBuffer::getCommandBuffer() const
{
	return commandBuffer;
}

void CommandBuffer::allocate(const LogicalDevice& device, const CommandPool& commandPool)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	VkResult result = vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to allocate command buffer");
		RenderUtils::checkVk(result);
	}
}

void CommandBuffer::free(const LogicalDevice& device, const CommandPool& commandPool)
{
	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
	commandBuffer = VK_NULL_HANDLE;
}

void CommandBuffer::begin(VkCommandBufferUsageFlags flags)
{
	if(running) return;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = flags;

	VkResult result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to begin recording command buffer");
		RenderUtils::checkVk(result);
	}

	running = true;
}

void CommandBuffer::end()
{
	if(!running) return;

	VkResult result = vkEndCommandBuffer(commandBuffer);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to record command buffer");
		RenderUtils::checkVk(result);
	}

	running = false;
}

void CommandBuffer::submit(const VkQueue& queue, const VkPipelineStageFlags& waitStages, const VkSemaphore& waitSemaphore, const VkSemaphore& signalSemaphore, VkFence fence)
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;
	if(waitStages != VK_NULL_HANDLE)
	{
		submitInfo.pWaitDstStageMask = &waitStages;
	}
	if(waitSemaphore != VK_NULL_HANDLE)
	{
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &waitSemaphore;
	}
	if(signalSemaphore != VK_NULL_HANDLE)
	{
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &signalSemaphore;
	}

	VkResult result = vkQueueSubmit(queue, 1, &submitInfo, fence);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to submit draw command buffer");
		RenderUtils::checkVk(result);
	}
}
