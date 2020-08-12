
#include "StdAfx.hpp"
#include "Render2D.hpp"

#include "Phronesis/SceneManagement/Component.ext.hpp"
#ifdef USING_SFML
#include "Phronesis/Components/Platform/SFMLRender2D.hpp"
#endif

using namespace Phronesis;

Render2D::Render2D()
#ifdef USING_SFML
	: impl(std::make_unique<SFMLRender2D>())
#endif
{
}

void Render2D::start()
{
	sortOrder = 0;
}

void Render2D::update()
{
	
}

void Render2D::setSortOrder(const int& order)
{
	sortOrder = order;
}

const int& Render2D::getSortOrder() const
{
	return sortOrder;
}

void Render2D::setRenderable(std::shared_ptr<Renderable2D> renderable)
{
	impl->setRenderable(renderable);
}

Render2DImpl* Render2D::getImpl() const
{
	return impl.get();
}
