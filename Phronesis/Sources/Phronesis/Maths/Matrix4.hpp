#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vector3.hpp"

namespace Phronesis
{
	typedef glm::mat4 Matrix4;

	namespace Transformation
	{
		Matrix4 translate(Matrix4 mat, Vector3 v);
		Matrix4 rotate(Matrix4 mat, float angle, Vector3 v);
		Matrix4 scale(Matrix4 mat, Vector3 v);
		
		Matrix4 perspective(float fovY, float aspectRatio, float zNear, float zFar);
		Matrix4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);

		Matrix4 lookAt(Vector3 eye, Vector3 centre, Vector3 up);
	}
}
