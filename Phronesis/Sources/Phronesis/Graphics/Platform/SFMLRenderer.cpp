
#include "StdAfx.hpp"
#include "SFMLRenderer.hpp"

#include "Phronesis/Core/Module.ext.hpp"
#include "Phronesis/Graphics/Platform/SFMLWindow.hpp"
#include "Phronesis/Components/Platform/SFMLRender2D.hpp"
#include "Phronesis/SceneManagement/Scenes.hpp"

using namespace Phronesis;

void SFMLRenderer::init()
{
	if(Module::hasModule<Window>())
	{
		window = static_cast<SFMLWindow*>(Module::getModule<Window>()->getImpl())->getWindow();
	}
	else
	{
		Log::error("Renderer module couldn't find Window module");
	}
}

void SFMLRenderer::update()
{
	// No window, skip update
	if(window == nullptr) return;
	if(populateRenders)
	{
		if(Module::hasModule<Scenes>())
		{
			auto scenesModule = Module::getModule<Scenes>();
			if(scenesModule->getCurrentScene() != nullptr)
			{		
				render2Ds = scenesModule->getAll<Render2D>();
				Log::debug("{} Render2D(s) found", render2Ds.size());
				populateRenders = false;
			}
		}
		else
		{
			populateRenders = false;
			Log::error("Renderer module couldn't find Scenes module");
		}
	}

	window->clear(sf::Color::Black);

	for(auto rend : render2Ds)
	{
		if(rend != nullptr && rend->getImpl() != nullptr)
		{
			window->draw(*static_cast<SFMLRender2D*>(rend->getImpl()));
		}
	}

	window->display();
}

void SFMLRenderer::dispose()
{
	render2Ds.clear();
	window = nullptr;
}

void SFMLRenderer::requestResize()
{
	framebufferResized = true;
}
