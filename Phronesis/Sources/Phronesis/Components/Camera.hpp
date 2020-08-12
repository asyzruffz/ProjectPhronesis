#pragma once

#include "Phronesis/SceneManagement/Component.hpp"
#include "Phronesis/Maths/Matrix4.hpp"

namespace Phronesis
{
	class Camera : public Component
	{
	public:
		Camera();
		
		void start() override;
		void update() override;

		void setFov(const float& angle);
		const float& getFov() const;

		const Matrix4& getViewMatrix() const;
		const Matrix4& getProjectionMatrix() const;

	private:
		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;

		float fov;
	};
}
