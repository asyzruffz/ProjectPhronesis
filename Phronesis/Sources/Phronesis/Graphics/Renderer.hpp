#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "Phronesis/Core/Module.hpp"
#include "Instance.hpp"
#include "Surface.hpp"
#include "PhysicalDevice.hpp"
#include "LogicalDevice.hpp"

namespace Phronesis
{
	class Renderer : public Module
	{
	public:
		void init();
		void update() override;
		void dispose();

		void requestResize();

	private:
		Instance instance;
		Surface surface;
		PhysicalDevice physicalDevice;
		LogicalDevice device;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;
		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		size_t currentFrame = 0;

		bool framebufferResized = false;

	private:
		void createSwapChain();
		void createImageViews();
		void createRenderPass();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();

		void recreateSwapChain();
		void cleanupSwapChain();
		void drawFrame();
	};
}
