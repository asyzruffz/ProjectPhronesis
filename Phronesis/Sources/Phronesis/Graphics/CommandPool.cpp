
#include "StdAfx.hpp"
#include "CommandPool.hpp"

#include "LogicalDevice.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

CommandPool::CommandPool() :
	commandPool(VK_NULL_HANDLE)
{
}

CommandPool::operator const VkCommandPool&() const
{
	return commandPool;
}

const VkCommandPool& CommandPool::getCommandPool() const
{
	return commandPool;
}

void CommandPool::create(const LogicalDevice& device)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = device.getGraphicsFamily();
	poolInfo.flags = 0; // Optional
	// we will only record the command buffers at the beginning of the program and 
	// then execute them many times in the main loop, so we're not going to use the flag

	VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create command pool");
		RenderUtils::checkVk(result);
	}
}

void CommandPool::dispose(const LogicalDevice& device)
{
	vkDestroyCommandPool(device, commandPool, nullptr);
}
