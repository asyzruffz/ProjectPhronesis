#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "Phronesis/Core/Module.hpp"

struct GLFWwindow;

namespace Phronesis
{
	class Renderer : public Module
	{
	public:
		void initWindow(int width, int height, const char* title);
		void initVulkan();
		void update() override;
		void disposeVulkan();
		void disposeWindow();

		void triggerFramebufferResize();

	private:
		GLFWwindow* window;

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		VkSurfaceKHR surface;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;

		VkQueue graphicsQueue;
		VkQueue presentationQueue;

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
		void createInstance();
		void setupDebugMessenger();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
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

		std::vector<const char*> getRequiredExtensions();
	};
}
