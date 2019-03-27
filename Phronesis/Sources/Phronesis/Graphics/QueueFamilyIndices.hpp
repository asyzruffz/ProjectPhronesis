#pragma once

#include <optional>

namespace Phronesis
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentationFamily;
		bool isComplete();
	};
}
