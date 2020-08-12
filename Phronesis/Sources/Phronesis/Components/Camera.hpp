#pragma once

#include <memory>

#include "Phronesis/SceneManagement/Component.hpp"
#include "Phronesis/Maths/Matrix4.hpp"

namespace Phronesis
{
	class CameraImpl
	{
	public:
		virtual ~CameraImpl() = default;
		virtual void start() = 0;
		virtual void update() = 0;
		virtual void setZoom(const float& scale) = 0;
		virtual const float& getZoom() const = 0;
		virtual void setFov(const float& angle) = 0;
		virtual const float& getFov() const = 0;
	};

	class Camera : public Component
	{
	public:
		Camera();
		
		void start() override;
		void update() override;

		void setZoom(const float& scale);
		const float& getZoom() const;
		void setFov(const float& angle);
		const float& getFov() const;

		const Matrix4& getViewMatrix() const;
		const Matrix4& getProjectionMatrix() const;

		CameraImpl* getImpl() const;

	private:
		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;

		std::unique_ptr<CameraImpl> impl;
	};
}
