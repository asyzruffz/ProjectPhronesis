
#include "StdAfx.hpp"
#include "Renderer.hpp"

#ifdef USING_VULKAN
#include "Phronesis/Graphics/Platform/VulkanRenderer.hpp"
#elif defined(USING_SFML)
#include "Phronesis/Graphics/Platform/SFMLRenderer.hpp"
#endif

using namespace Phronesis;

Renderer::Renderer() :
#ifdef USING_VULKAN
	impl(std::make_unique<VulkanRenderer>())
#elif defined(USING_SFML)
	impl(std::make_unique<SFMLRenderer>())
#endif
{
}

void Renderer::init()
{
#ifdef USING_VULKAN
	Log::info("Using Vulkan implementation");
#elif defined(USING_SFML)
	Log::info("Using SFML implementation");
#endif

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
