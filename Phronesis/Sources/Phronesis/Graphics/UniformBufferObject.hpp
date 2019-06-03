#pragma once

#include "Phronesis/Maths/Matrix4.hpp"

namespace Phronesis
{
	struct UniformBufferObject
	{
		Matrix4 model;
		Matrix4 view;
		Matrix4 proj;
	};
}
