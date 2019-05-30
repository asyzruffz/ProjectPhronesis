#pragma once

#include <array>

#include <vulkan/vulkan.h>

#include <Phronesis/Maths.hpp>

namespace Phronesis
{
	struct Vertex
	{
		Vector2 pos;
		Vector3 color;

		static VkVertexInputBindingDescription getBindingDescription();
		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
	};
}
