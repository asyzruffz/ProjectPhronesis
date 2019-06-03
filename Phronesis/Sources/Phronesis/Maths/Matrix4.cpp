
#include "StdAfx.hpp"
#include "Matrix4.hpp"

using namespace Phronesis;

Matrix4 Transformation::translate(Matrix4 mat, Vector3 v)
{
	return glm::translate(mat, v);
}

Matrix4 Transformation::rotate(Matrix4 mat, float angle, Vector3 v)
{
	return glm::rotate(mat, angle, v);
}

Matrix4 Transformation::scale(Matrix4 mat, Vector3 v)
{
	return glm::scale(mat, v);
}

Matrix4 Transformation::perspective(float fovY, float aspectRatio, float zNear, float zFar)
{
	return glm::perspective(fovY, aspectRatio, zNear, zFar);
}

Matrix4 Transformation::ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	return glm::ortho(left, right, bottom, top, zNear, zFar);
}

Matrix4 Transformation::lookAt(Vector3 eye, Vector3 centre, Vector3 up)
{
	return glm::lookAt(eye, centre, up);
}
