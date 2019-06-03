#pragma once

#include "Buffer.hpp"

namespace Phronesis
{
	class LogicalDevice;

	class UniformBuffer : public Buffer
	{
	public:
		void update(const LogicalDevice& device, const void* data);
	};
}
