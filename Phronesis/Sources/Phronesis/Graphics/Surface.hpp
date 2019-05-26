#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class Instance;
	class PhysicalDevice;

	class Surface
	{
	public:
		Surface();

		operator const VkSurfaceKHR&() const;
		const VkSurfaceKHR& getSurface() const;

		void create(const Instance& instance);
		void dispose(const Instance& instance);

		void acquireProperties(const PhysicalDevice& device);

		const VkSurfaceCapabilitiesKHR& getCapabilities() const;
		const std::vector<VkSurfaceFormatKHR>& getFormats() const;
		const std::vector<VkPresentModeKHR>& getPresentationModes() const;

		static std::pair<std::vector<VkSurfaceFormatKHR>, std::vector<VkPresentModeKHR>> querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

	private:
		VkSurfaceKHR surface;

		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentationModes;
	};
}
