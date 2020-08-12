
#include "StdAfx.hpp"
#include "Window.hpp"

#ifdef USING_GLFW
#include "Phronesis/Graphics/Platform/GLFWWindow.hpp"
#elif defined(USING_SFML)
#include "Phronesis/Graphics/Platform/SFMLWindow.hpp"
#endif

using namespace Phronesis;

Window::Window() :
#ifdef USING_GLFW
	impl(std::make_unique<GLFWWindow>())
#elif defined(USING_SFML)
	impl(std::make_unique<SFMLWindow>())
#endif
{
}

void Window::init(unsigned int width, unsigned int height, const char* title)
{
	size.x = width; size.y = height;
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
