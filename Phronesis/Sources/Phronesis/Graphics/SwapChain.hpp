#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class Surface;

	class SwapChain
	{
	public:
		SwapChain();

		operator const VkSwapchainKHR&() const;
		const VkSwapchainKHR& getSwapChain() const;

		void create(const LogicalDevice& device, const Surface& surface);
		void dispose(const LogicalDevice& device);

		VkResult acquireNextImage(const LogicalDevice& device, unsigned int* imageIndex, const VkSemaphore& presentationCompleteSemaphore = VK_NULL_HANDLE);
		VkResult queuePresentation(const VkQueue &queue, unsigned int* imageIndex, const VkSemaphore &waitSemaphore = VK_NULL_HANDLE);

		const VkExtent2D& getExtent() const;
		const std::vector<VkImage>& getImages() const;
		const std::vector<VkImageView>& getImageViews() const;
		const VkFormat& getImageFormat() const;

	private:
		VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		void createImageViews(const LogicalDevice& device);

	private:
		VkSwapchainKHR swapChain;

		VkExtent2D extent;

		std::vector<VkImage> images;
		std::vector<VkImageView> imageViews;
		VkFormat imageFormat;
	};
}
