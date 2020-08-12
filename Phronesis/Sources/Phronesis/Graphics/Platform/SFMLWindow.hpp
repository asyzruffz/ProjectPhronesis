#pragma once

#include <vector>

//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Phronesis/Graphics/Window.hpp"

namespace Phronesis
{
	class SFMLWindow : public WindowImpl
	{
	public:
		void init(unsigned int width, unsigned int height, const char* title) override;
		void update() override;
		void dispose() override;

		void handleMinimize() override;
		sf::RenderWindow* getWindow();

		//std::vector<const char*> getRequiredExtensions() const;

		//void createSurface(const VkInstance& instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) const;

	private:
		void triggerResize(unsigned int width, unsigned int height);

	private:
		sf::RenderWindow window;
	};
}
