#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Phronesis/Graphics/Renderer.hpp"

namespace Phronesis
{
	class Render2D;

	class SFMLRenderer : public RendererImpl
	{
	public:
		void init() override;
		void update() override;
		void dispose() override;
		void requestResize() override;

	private:
		sf::RenderWindow* window = nullptr;
		std::vector<Render2D*> render2Ds;
		bool framebufferResized = false;
		bool populateRenders = true;
	};
}
