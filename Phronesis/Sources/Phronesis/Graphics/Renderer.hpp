#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "Phronesis/Core/Module.hpp"
#include "Instance.hpp"
#include "Surface.hpp"
#include "PhysicalDevice.hpp"
#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"
#include "FrameBuffers.hpp"
#include "GraphicsPipeline.hpp"

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

		SwapChain swapChain;
		RenderPass renderPass;
		FrameBuffers frameBuffers;

		GraphicsPipeline graphicsPipeline;

		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		size_t currentFrame = 0;

		bool framebufferResized = false;

	private:
		void createGraphicsPipeline();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();

		void recreateSwapChain();
		void cleanupSwapChain();
		void drawFrame();
	};
}
