
#include "StdAfx.hpp"
#include "Buffer.hpp"

#include "LogicalDevice.hpp"
#include "PhysicalDevice.hpp"
#include "CommandPool.hpp"
#include "CommandBuffer.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

Buffer::Buffer() :
	buffer(VK_NULL_HANDLE),
	memory(VK_NULL_HANDLE)
{
}

Buffer::operator const VkBuffer&() const
{
	return buffer;
}

const VkBuffer& Buffer::getBuffer() const
{
	return buffer;
}

void Buffer::create(const LogicalDevice& device, const VkDeviceSize& size, const VkBufferUsageFlags& usage)
{
	this->size = size;

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	VkResult result = vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create vertex buffer");
		RenderUtils::checkVk(result);
	}
}

void Buffer::dispose(const LogicalDevice & device)
{
	vkDestroyBuffer(device, buffer, nullptr);

	if(memory != VK_NULL_HANDLE)
	{
		vkFreeMemory(device, memory, nullptr);
		memory = VK_NULL_HANDLE;
	}
}

void Buffer::allocateMemory(const LogicalDevice& logicalDevice, const PhysicalDevice& physicalDevice, VkMemoryPropertyFlags properties, const void* data)
{
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(logicalDevice, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

	VkResult result = vkAllocateMemory(logicalDevice, &allocInfo, nullptr, &memory);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to allocate vertex buffer memory");
		RenderUtils::checkVk(result);
	}

	vkBindBufferMemory(logicalDevice, buffer, memory, 0);

	// if a pointer to the buffer data has been passed, map the buffer and copy over the data.
	if(data != nullptr)
	{
		void* mapped;
		vkMapMemory(logicalDevice, memory, 0, size, 0, &mapped);
			memcpy(mapped, data, (size_t)size);
		vkUnmapMemory(logicalDevice, memory);
	}
}

uint32_t Buffer::findMemoryType(const PhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	auto memProperties = physicalDevice.getMemoryProperties();
	for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	throw std::runtime_error("[ERROR] [Vulkan] Failed to find suitable memory type");
}

const VkDeviceSize& Buffer::getSize() const
{
	return size;
}

const VkDeviceMemory& Buffer::getMemory() const
{
	return memory;
}

void Buffer::copy(const LogicalDevice& device, const CommandPool& commandPool, const Buffer& srcBuffer, const Buffer& dstBuffer)
{
	// allocate a temporary command buffer
	CommandBuffer commandBuffer;
	commandBuffer.allocate(device, commandPool);

	commandBuffer.begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
		VkBufferCopy copyRegion = {};
		copyRegion.size = dstBuffer.getSize();
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
	commandBuffer.end();

	commandBuffer.submit(device.getGraphicsQueue());
	vkQueueWaitIdle(device.getGraphicsQueue());

	commandBuffer.free(device, commandPool);
}
