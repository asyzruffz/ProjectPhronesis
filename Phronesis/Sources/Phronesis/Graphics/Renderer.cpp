
#include "StdAfx.hpp"
#include "Renderer.hpp"

#include "Phronesis/Core/Engine.hpp"
#include "Phronesis/FileIO/BinaryFile.hpp"
#include "Window.hpp"
#include "RenderUtils.hpp"

#include <GLFW/glfw3.h>

using namespace Phronesis;


const int MAX_FRAMES_IN_FLIGHT = 2;

void Renderer::init()
{
	// create surface
	surface.create(instance);

	// pick physical device
	physicalDevice.pick(instance, surface);

	// acquire the basic surface capabilities, supported surface formats & supported presentation modes
	surface.acquireProperties(physicalDevice);

	// create logical device (and queues)
	device.create(physicalDevice, surface);

	// create swap chain (and image views)
	swapChain.create(device, surface);

	// create render pass
	renderPass.create(device, swapChain);

	createGraphicsPipeline();

	// create frame buffers
	frameBuffers.create(device, swapChain, renderPass);

	// create command pool
	commandPool.create(device);

	createCommandBuffers();
	createSyncObjects();
}

void Renderer::update()
{
	drawFrame();
}

void Renderer::dispose()
{
	// wait if device is busy
	vkDeviceWaitIdle(device);

	cleanupSwapChain();

	// destroy semaphores and fences
	for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(device, inFlightFences[i], nullptr);
	}

	// destroy command pool
	commandPool.dispose(device);

	// destroy logical device (and queues)
	device.dispose();

	// destroy window surface
	surface.dispose(instance);
}

void Renderer::requestResize()
{
	framebufferResized = true;
}

void Renderer::createGraphicsPipeline()
{
	auto vertShaderCode = BinaryFile::read("Shaders/shader_base.vert.spv");
	auto fragShaderCode = BinaryFile::read("Shaders/shader_base.frag.spv");

	// create shader modules
	VkShaderModule vertShaderModule = RenderUtils::createShaderModule(device, vertShaderCode);
	VkShaderModule fragShaderModule = RenderUtils::createShaderModule(device, fragShaderCode);

	// create shader stages
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	// createGraphicsPipeline
	graphicsPipeline.create(device, swapChain, shaderStages, renderPass);

	// destroy shader modules
	vkDestroyShaderModule(device, fragShaderModule, nullptr);
	vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

void Renderer::createCommandBuffers()
{
	commandBuffers.resize(frameBuffers.size());
	for(auto& commandBuffer : commandBuffers)
	{
		commandBuffer.allocate(device, commandPool);
	}

	for(size_t i = 0; i < commandBuffers.size(); i++)
	{
		commandBuffers[i].begin();

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = frameBuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChain.getExtent();

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			graphicsPipeline.bind(commandBuffers[i]);

			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffers[i]);

		commandBuffers[i].end();
	}
}

void Renderer::createSyncObjects()
{
	// create semaphores and fences
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		VkResult result1 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
		VkResult result2 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
		VkResult result3 = vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]);
		if(result1 != VK_SUCCESS || result2 != VK_SUCCESS || result3 != VK_SUCCESS)
		{
			Log::error("[Vulkan] Failed to create synchronization objects for a frame");
			RenderUtils::checkVk(result1);
			RenderUtils::checkVk(result2);
			RenderUtils::checkVk(result3);
		}
	}
}

void Renderer::recreateSwapChain()
{
	getModule<Window>()->handleMinimize();

	vkDeviceWaitIdle(device);
	cleanupSwapChain();

	// recreate objects that depend on the swap chain or the window size
	swapChain.create(device, surface);
	renderPass.create(device, swapChain);
	createGraphicsPipeline();
	frameBuffers.create(device, swapChain, renderPass);
	createCommandBuffers();
}

void Renderer::cleanupSwapChain()
{
	// destroy framebuffers
	frameBuffers.dispose(device);

	// clean up the existing command buffers instead of destroying it
	for(auto& commandBuffer : commandBuffers)
	{
		commandBuffer.free(device, commandPool);
	}

	// destroy graphics pipeline (and pipeline layout)
	graphicsPipeline.dispose(device);

	// destroy render pass
	renderPass.dispose(device);

	// destroy swap chain (and image views)
	swapChain.dispose(device);
}

void Renderer::drawFrame()
{
	// fence waits for available frame
	vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	// semaphores to signal that an image has been acquired and is ready for rendering
	//		  and to signal that rendering has finished and presentation can happen
	VkSemaphore& waitSemaphore = imageAvailableSemaphores[currentFrame];
	VkSemaphore& signalSemaphore = renderFinishedSemaphores[currentFrame];

	// acquire an image from the swap chain
	unsigned int imageIndex;
	VkResult result = swapChain.acquireNextImage(device, &imageIndex, waitSemaphore);
	if(result == VK_ERROR_OUT_OF_DATE_KHR)
	{	// the swap chain has become incompatible with the surface
		// usually happens after a window resize
		recreateSwapChain();
		return;
	}

	vkResetFences(device, 1, &inFlightFences[currentFrame]);

	// submit the command buffer
	commandBuffers[imageIndex].submit(device.getGraphicsQueue(), waitSemaphore, signalSemaphore, inFlightFences[currentFrame]);

	// submit the result back to the swap chain to have it show up on the screen
	result = swapChain.queuePresentation(device.getPresentationQueue(), &imageIndex, signalSemaphore);
	if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
	{	// also recreate the swap chain if it is suboptimal
		recreateSwapChain();
		framebufferResized = false;
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
