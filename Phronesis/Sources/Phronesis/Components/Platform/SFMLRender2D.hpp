#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Phronesis/Components/Render2D.hpp"

namespace Phronesis
{
	class SFMLRender2D : public sf::Drawable, public Render2DImpl
	{
	public:
		SFMLRender2D();

		void setRenderable(std::shared_ptr<Renderable2D> renderable) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::weak_ptr<Renderable2D> drawable;
	};
}
