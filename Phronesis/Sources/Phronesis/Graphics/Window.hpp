#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "Phronesis/Core/Module.hpp"
#include "Phronesis/Maths/Vector2.hpp"

struct GLFWwindow;

namespace Phronesis
{
	class Window : public Module
	{
	public:
		void init(unsigned int width, unsigned int height, const char* title);
		void update() override;
		void dispose();

		const Vector2ui& getSize() const;
		const float getAspectRatio() const;

		std::vector<const char*> getRequiredExtensions() const;

		VkResult createSurface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const;

		void triggerResize(unsigned int width, unsigned int height);
		void handleMinimize();

	private:
		GLFWwindow* window;

		Vector2ui size;
	};
}
