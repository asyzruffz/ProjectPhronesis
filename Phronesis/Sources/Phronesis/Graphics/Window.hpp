#pragma once

#include <memory>

#include "Phronesis/Core/Module.hpp"
#include "Phronesis/Maths/Vector2.hpp"

namespace Phronesis
{
	class WindowImpl
	{
	public:
		virtual void init(unsigned int width, unsigned int height, const char* title) = 0;
		virtual void update() = 0;
		virtual void dispose() = 0;
		virtual void handleMinimize() = 0;
	};

	class Window : public Module
	{
	public:
		void init(unsigned int width, unsigned int height, const char* title);
		void update() override;
		void dispose() override;

		void handleMinimize();

		const Vector2ui& getSize() const;
		void setSize(unsigned int width, unsigned int height);
		const float getAspectRatio() const;

		WindowImpl* getImpl() const;

	private:
		Vector2ui size;
		std::unique_ptr<WindowImpl> impl;
	};
}
