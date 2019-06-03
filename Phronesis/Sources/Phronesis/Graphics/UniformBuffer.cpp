
#include "StdAfx.hpp"
#include "UniformBuffer.hpp"

#include "LogicalDevice.hpp"

using namespace Phronesis;

void UniformBuffer::update(const LogicalDevice& device, const void* data)
{
	void* mapped;
	vkMapMemory(device, memory, 0, size, 0, &mapped);
		memcpy(mapped, data, (size_t)size);
	vkUnmapMemory(device, memory);
}
