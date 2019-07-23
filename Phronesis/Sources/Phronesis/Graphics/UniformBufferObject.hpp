#pragma once

#include "Phronesis/Maths/Matrix4.hpp"

namespace Phronesis
{
	struct UniformBufferObject
	{
		alignas(16) Matrix4 model;
		alignas(16) Matrix4 view;
		alignas(16) Matrix4 proj;
	};
}
