
#include "StdAfx.hpp"
#include "Camera.hpp"

#include "Phronesis/SceneManagement/Component.ext.hpp"
#include "Phronesis/Core.hpp"
#include "Phronesis/Graphics/Window.hpp"
#ifdef USING_SFML
#include "Phronesis/Components/Platform/SFMLCamera.hpp"
#endif

using namespace Phronesis;

Camera::Camera() :
#ifdef USING_SFML
	impl(std::make_unique<SFMLCamera>()),
#endif
	viewMatrix(Matrix4(1.0f)),
	projectionMatrix(Matrix4(1.0f))
{
}

void Camera::start()
{
	impl->start();
}

void Camera::update()
{
	impl->update();
	//viewMatrix = Transformation::lookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3::zero, Vector3::forward);
	//projectionMatrix = Transformation::perspective(glm::radians(fov), Module::getModule<Window>()->getAspectRatio(), 0.1f, 10.0f);
}

void Camera::setZoom(const float& scale)
{
	impl->setZoom(scale);
}

const float& Camera::getZoom() const
{
	return impl->getZoom();
}

void Camera::setFov(const float& angle)
{
	impl->setFov(angle);
}

const float& Camera::getFov() const
{
	return impl->getFov();
}

const Matrix4& Camera::getViewMatrix() const
{
	return viewMatrix;
}

const Matrix4& Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

CameraImpl* Camera::getImpl() const
{
	return impl.get();
}
