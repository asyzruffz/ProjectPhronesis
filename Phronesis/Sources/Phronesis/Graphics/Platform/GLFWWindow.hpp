#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "Phronesis/Graphics/Window.hpp"

struct GLFWwindow;

namespace Phronesis
{
	class GLFWWindow : public WindowImpl
	{
	public:
		void init(unsigned int width, unsigned int height, const char* title) override;
		void update() override;
		void dispose() override;

		void handleMinimize() override;

		std::vector<const char*> getRequiredExtensions() const;

		void createSurface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const;

		void triggerResize(unsigned int width, unsigned int height);

	private:
		GLFWwindow* window;
	};
}
