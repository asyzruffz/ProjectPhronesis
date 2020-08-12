
#include "StdAfx.hpp"
#include "Circle.hpp"

#include "Phronesis/SceneManagement/Component.ext.hpp"

using namespace Phronesis;

Circle::Circle(const float& radius) :
	rad(radius)
{
}

void Circle::start()
{
	if(has<Render2D>())
	{
		get<Render2D>().setRenderable(std::dynamic_pointer_cast<Renderable2D>(shared_from_this()));
	}
	else
	{
		Log::error("Circle missing a Render2D component");
	}
}

const float& Circle::getRadius() const
{
	return rad;
}

void Circle::setRadius(const float& radius)
{
	rad = radius;
}
