
#include "StdAfx.hpp"
#include "Camera.hpp"

#include "Phronesis/SceneManagement/Component.ext.hpp"
#include "Phronesis/Core.hpp"
#include "Phronesis/Graphics/Window.hpp"

using namespace Phronesis;

Camera::Camera() :
	viewMatrix(Matrix4(1.0f)),
	projectionMatrix(Matrix4(1.0f)),
	fov(60.0f)
{
}

void Camera::start()
{
	
}

void Camera::update()
{
	viewMatrix = Transformation::lookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3::zero, Vector3::forward);
	projectionMatrix = Transformation::perspective(glm::radians(fov), Module::getModule<Window>()->getAspectRatio(), 0.1f, 10.0f);
}

void Camera::setFov(const float& angle)
{
	fov = angle;
}

const float& Camera::getFov() const
{
	return fov;
}

const Matrix4& Camera::getViewMatrix() const
{
	return viewMatrix;
}

const Matrix4& Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}
