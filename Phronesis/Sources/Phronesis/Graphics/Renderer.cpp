
#include "StdAfx.hpp"
#include "Renderer.hpp"

#include "Phronesis/Graphics/Platform/VulkanRenderer.hpp"

using namespace Phronesis;

void Renderer::init()
{
	impl = std::make_unique<VulkanRenderer>();
	impl->init();
}

void Renderer::update()
{
	impl->update();
}

void Renderer::dispose()
{
	impl->dispose();
}

void Renderer::requestResize()
{
	impl->requestResize();
}
