#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class PhysicalDevice;

	class Buffer
	{
	public:
		Buffer();
		virtual ~Buffer() = default;

		operator const VkBuffer&() const;
		const VkBuffer& getBuffer() const;

		virtual void create(const LogicalDevice& device, const VkDeviceSize& size, const VkBufferUsageFlags& usage);
		virtual void dispose(const LogicalDevice& device);

		void allocateMemory(const LogicalDevice& logicalDevice, const PhysicalDevice& physicalDevice, const void* data = nullptr);

		static uint32_t findMemoryType(const PhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		const VkDeviceSize& getSize() const;
		const VkDeviceMemory& getMemory() const;

	protected:
		VkBuffer buffer;
		VkDeviceSize size;
		VkDeviceMemory memory;
	};
}
