#pragma once

#include <memory>

#include "Phronesis/SceneManagement/Component.hpp"

namespace Phronesis
{
	class Renderable2D {};

	class Render2DImpl
	{
	public:
		virtual ~Render2DImpl() = default;
		virtual void setRenderable(std::shared_ptr<Renderable2D> renderable) = 0;
	};

	class Render2D : public Component
	{
	public:
		Render2D();
		
		void start() override;
		void update() override;

		void setSortOrder(const int& order);
		const int& getSortOrder() const;

		void setRenderable(std::shared_ptr<Renderable2D> renderable);

		Render2DImpl* getImpl() const;

	private:
		int sortOrder;
		std::unique_ptr<Render2DImpl> impl;
	};
}
