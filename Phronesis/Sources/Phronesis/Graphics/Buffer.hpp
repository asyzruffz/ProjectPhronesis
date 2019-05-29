#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class PhysicalDevice;
	class CommandPool;

	class Buffer
	{
	public:
		Buffer();
		virtual ~Buffer() = default;

		operator const VkBuffer&() const;
		const VkBuffer& getBuffer() const;

		virtual void create(const LogicalDevice& device, const VkDeviceSize& size, const VkBufferUsageFlags& usage);
		virtual void dispose(const LogicalDevice& device);

		void allocateMemory(const LogicalDevice& logicalDevice, const PhysicalDevice& physicalDevice, VkMemoryPropertyFlags properties, const void* data = nullptr);

		static uint32_t findMemoryType(const PhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		const VkDeviceSize& getSize() const;
		const VkDeviceMemory& getMemory() const;

		static void copy(const LogicalDevice& device, const CommandPool& commandPool, const Buffer& srcBuffer, const Buffer& dstBuffer);

	protected:
		VkBuffer buffer;
		VkDeviceSize size;
		VkDeviceMemory memory;
	};
}
