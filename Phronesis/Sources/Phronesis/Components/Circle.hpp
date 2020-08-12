#pragma once

#include "Phronesis/SceneManagement/Component.hpp"
#include "Render2D.hpp"

namespace Phronesis
{
	class Circle : public Component, public Renderable2D
	{
	public:
		Circle(const float& radius);

		void start() override;

		const float& getRadius() const;
		void setRadius(const float& radius);

	private:
		float rad;
	};
}
