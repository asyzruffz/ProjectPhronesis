#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "Phronesis/Graphics/Renderer.hpp"
#include "Phronesis/Graphics/Instance.hpp"
#include "Phronesis/Graphics/Surface.hpp"
#include "Phronesis/Graphics/PhysicalDevice.hpp"
#include "Phronesis/Graphics/LogicalDevice.hpp"
#include "Phronesis/Graphics/SwapChain.hpp"
#include "Phronesis/Graphics/RenderPass.hpp"
#include "Phronesis/Graphics/FrameBuffers.hpp"
#include "Phronesis/Graphics/GraphicsPipeline.hpp"
#include "Phronesis/Graphics/CommandPool.hpp"
#include "Phronesis/Graphics/DescriptorSets.hpp"
#include "Phronesis/Graphics/Buffer.hpp"
#include "Phronesis/Graphics/UniformBuffer.hpp"
#include "Phronesis/Graphics/CommandBuffer.hpp"

namespace Phronesis
{
	class VulkanRenderer : public RendererImpl
	{
	public:
		void init() override;
		void update() override;
		void dispose() override;

		void requestResize() override;

	private:
		Instance instance;
		Surface surface;
		PhysicalDevice physicalDevice;
		LogicalDevice device;

		SwapChain swapChain;
		RenderPass renderPass;
		FrameBuffers frameBuffers;

		GraphicsPipeline graphicsPipeline;

		CommandPool commandPool;

		Buffer vertexBuffer;
		Buffer indexBuffer;

		std::vector<UniformBuffer> uniformBuffers;

		DescriptorSets descriptorSets;

		std::vector<CommandBuffer> commandBuffers;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		size_t currentFrame = 0;

		bool framebufferResized = false;

	private:
		void createCommandBuffers();
		void createSyncObjects();

		void recreateSwapChain();
		void cleanupSwapChain();

		void drawFrame();
		void updateUniformBuffer(uint32_t currentImage);
	};
}
