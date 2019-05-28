
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

	createCommandPool();
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
	vkDestroyCommandPool(device, commandPool, nullptr);

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

void Renderer::createCommandPool()
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = device.getGraphicsFamily();
	poolInfo.flags = 0; // Optional
	// we will only record the command buffers at the beginning of the program and 
	// then execute them many times in the main loop, so we're not going to use the flag

	VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create command pool");
		RenderUtils::checkVk(result);
	}
}

void Renderer::createCommandBuffers()
{
	commandBuffers.resize(frameBuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	VkResult result = vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data());
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to allocate command buffers");
		RenderUtils::checkVk(result);
	}

	for(size_t i = 0; i < commandBuffers.size(); i++)
	{
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		result = vkBeginCommandBuffer(commandBuffers[i], &beginInfo);
		if(result != VK_SUCCESS)
		{
			Log::error("[Vulkan] Failed to begin recording command buffer");
			RenderUtils::checkVk(result);
		}

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

		result = vkEndCommandBuffer(commandBuffers[i]);
		if(result != VK_SUCCESS)
		{
			Log::error("[Vulkan] Failed to record command buffer");
			RenderUtils::checkVk(result);
		}
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
	vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

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

	// acquire an image from the swap chain
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(device, swapChain, std::numeric_limits<uint64_t>::max(),
								imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
	if(result == VK_ERROR_OUT_OF_DATE_KHR)
	{	// the swap chain has become incompatible with the surface
		// usually happens after a window resize
		recreateSwapChain();
		return;
	}
	else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		Log::error("[Vulkan] Failed to acquire swap chain image");
		RenderUtils::checkVk(result);
	}

	vkResetFences(device, 1, &inFlightFences[currentFrame]);

	// semaphores to signal that an image has been acquired and is ready for rendering
	//		  and to signal that rendering has finished and presentation can happen
	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };

	// submit the command buffer
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	result = vkQueueSubmit(device.getGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to submit draw command buffer");
		RenderUtils::checkVk(result);
	}

	// submit the result back to the swap chain to have it show up on the screen
	VkSwapchainKHR swapChains[] = { swapChain };

	VkPresentInfoKHR presentationInfo = {};
	presentationInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentationInfo.waitSemaphoreCount = 1;
	presentationInfo.pWaitSemaphores = signalSemaphores;
	presentationInfo.swapchainCount = 1;
	presentationInfo.pSwapchains = swapChains;
	presentationInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(device.getPresentationQueue(), &presentationInfo);
	if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
	{	// also recreate the swap chain if it is suboptimal
		recreateSwapChain();
		framebufferResized = false;
	}
	else if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to present swap chain image");
		RenderUtils::checkVk(result);
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
