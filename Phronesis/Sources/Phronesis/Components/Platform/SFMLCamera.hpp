#pragma once

#include <SFML/Graphics.hpp>

#include "Phronesis/Components/Camera.hpp"

namespace Phronesis
{
	class SFMLCamera : public CameraImpl
	{
	public:
		SFMLCamera();

		void start() override;
		void update() override;

		void setZoom(const float& scale);
		const float& getZoom() const;
		void setFov(const float& angle) override;
		const float& getFov() const override;

	private:
		sf::View view;
		float zoom;
		float fov;
	};
}
