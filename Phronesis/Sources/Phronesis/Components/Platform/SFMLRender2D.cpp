
#include "StdAfx.hpp"
#include "SFMLRender2D.hpp"

#include "Phronesis/Components/Circle.hpp"

using namespace Phronesis;

SFMLRender2D::SFMLRender2D()
{
}

void SFMLRender2D::setRenderable(std::shared_ptr<Renderable2D> renderable)
{
	drawable = renderable;
}

void SFMLRender2D::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(auto drawable_ = drawable.lock())
	{
		auto circle = static_cast<Circle*>(drawable_.get());
		sf::CircleShape shape(circle->getRadius());
		shape.setFillColor(sf::Color(100, 250, 50));
		target.draw(shape, states);
	}
}
