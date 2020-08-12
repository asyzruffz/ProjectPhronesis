
#include "StdAfx.hpp"
#include "SFMLCamera.hpp"

#include "Phronesis/Core.hpp"
#include "Phronesis/Graphics/Platform/SFMLWindow.hpp"

using namespace Phronesis;

SFMLCamera::SFMLCamera() :
	zoom(1.0f),
	fov(60.f)
{
}

void SFMLCamera::start()
{
	auto window = static_cast<SFMLWindow*>(Module::getModule<Window>()->getImpl())->getWindow();
	
	view = window->getView();
	view.zoom(zoom);
	window->setView(view);
}

void SFMLCamera::update()
{
	auto window = static_cast<SFMLWindow*>(Module::getModule<Window>()->getImpl())->getWindow();
	
	view = window->getView();
	view.zoom(zoom);
	window->setView(view);
}

void SFMLCamera::setZoom(const float& scale)
{
	zoom = scale;
}

const float& SFMLCamera::getZoom() const
{
	return zoom;
}

void SFMLCamera::setFov(const float& angle)
{
	fov = angle;
}

const float& SFMLCamera::getFov() const
{
	return fov;
}
