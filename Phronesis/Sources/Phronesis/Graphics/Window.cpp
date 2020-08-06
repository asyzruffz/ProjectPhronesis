
#include "StdAfx.hpp"
#include "Window.hpp"

#include "Phronesis/Graphics/Platform/GLFWWindow.hpp"

using namespace Phronesis;

void Window::init(unsigned int width, unsigned int height, const char* title)
{
	size.x = width; size.y = height;

	impl = std::make_unique<GLFWWindow>();
	impl->init(width, height, title);
}

void Window::update()
{
	impl->update();
}

void Window::dispose()
{
	impl->dispose();
	//system("pause");
}

void Window::handleMinimize()
{
	impl->handleMinimize();
}

const Vector2ui& Window::getSize() const
{
	return size;
}

void Window::setSize(unsigned int width, unsigned int height)
{
	size.x = width; size.y = height;
}

const float Window::getAspectRatio() const
{
	return size.x / (float)size.y;
}

WindowImpl* Window::getImpl() const
{
	return impl.get();
}
