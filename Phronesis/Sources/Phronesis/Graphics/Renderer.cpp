
#include "StdAfx.hpp"
#include "Renderer.hpp"

#include "Phronesis/Core/Engine.hpp"
#include "Phronesis/FileIO/BinaryFile.hpp"
#include "Phronesis/FileIO/Directory.hpp"
#include "Phronesis/Maths/Matrix4.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "RenderUtils.hpp"
#include "Vertex.hpp"
#include "UniformBufferObject.hpp"

#include <GLFW/glfw3.h>

using namespace Phronesis;


const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<Vertex> vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	{{ 0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
	{{-0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}
};

const std::vector<unsigned int> indices = {
	0, 1, 2, 2, 3, 0
};

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

	// create shaders
	auto shaderFiles = Directory::getAllFilesIn("Shaders");

	std::vector<Shader> shaders;
	shaders.resize(shaderFiles.size());
	for(size_t i = 0; i < shaderFiles.size(); i++)
	{
		shaders[i].create(device, shaderFiles[i]);

		// extra for vertex shader
		if(shaders[i].getStage() & VK_SHADER_STAGE_VERTEX_BIT)
		{
			// add uniform buffer descriptor's descriptor pools
			shaders[i].setUniformDescriptor(swapChain.getImages().size());
		}
	}

	// create graphics pipeline
	graphicsPipeline.create(device, swapChain, shaders, renderPass);

	// destroy shaders
	for(auto& shader : shaders)
	{
		shader.dispose(device);
	}

	// create frame buffers
	frameBuffers.create(device, swapChain, renderPass);

	// create command pool
	commandPool.create(device);

	Buffer stagingBuffer;
	VkDeviceSize bufferSize;

	// create a staging buffer for mapping and copying the vertex data
	bufferSize = sizeof(vertices[0]) * vertices.size();
	stagingBuffer.create(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
	stagingBuffer.allocateMemory(device, physicalDevice, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertices.data());

	// create vertex buffer
	vertexBuffer.create(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
	vertexBuffer.allocateMemory(device, physicalDevice, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	// copy the contents from staging buffer to vertex buffer
	Buffer::copy(device, commandPool, stagingBuffer, vertexBuffer);

	// destroy the staging buffer
	stagingBuffer.dispose(device);

	// create a staging buffer for mapping and copying the index data
	bufferSize = sizeof(indices[0]) * indices.size();
	stagingBuffer.create(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
	stagingBuffer.allocateMemory(device, physicalDevice, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, indices.data());

	// create index buffer
	indexBuffer.create(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
	indexBuffer.allocateMemory(device, physicalDevice, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	// copy the contents from staging buffer to index buffer
	Buffer::copy(device, commandPool, stagingBuffer, indexBuffer);

	// destroy the staging buffer
	stagingBuffer.dispose(device);

	// create uniform buffers
	bufferSize = sizeof(UniformBufferObject);
	uniformBuffers.resize(swapChain.getImages().size());
	for(size_t i = 0; i < swapChain.getImages().size(); i++)
	{
		uniformBuffers[i].create(device, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		uniformBuffers[i].allocateMemory(device, physicalDevice, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	}

	// create descriptor sets to bind them to the uniform buffer descriptor
	descriptorSets.allocate(device, graphicsPipeline, swapChain.getImages().size());
	descriptorSets.configureDescriptors(device, uniformBuffers);

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

	// destroy index buffer
	indexBuffer.dispose(device);

	// destroy vertex buffer
	vertexBuffer.dispose(device);

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

void Renderer::createCommandBuffers()
{
	commandBuffers.resize(frameBuffers.size());
	for(auto& commandBuffer : commandBuffers)
	{
		commandBuffer.allocate(device, commandPool);
	}

	for(size_t i = 0; i < commandBuffers.size(); i++)
	{
		commandBuffers[i].begin(VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = frameBuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChain.getExtent();
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			graphicsPipeline.bind(commandBuffers[i]);

			VkDeviceSize offset = 0;
			vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &vertexBuffer.getBuffer(), &offset);
			vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getPipelineLayout(), 0, 1, &descriptorSets[i], 0, nullptr);

			vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

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

	auto shaderFiles = Directory::getAllFilesIn("Shaders");
	std::vector<Shader> shaders;
	shaders.resize(shaderFiles.size());
	for(size_t i = 0; i < shaderFiles.size(); i++) {
		shaders[i].create(device, shaderFiles[i]);
	}

	graphicsPipeline.create(device, swapChain, shaders, renderPass);

	for(auto& shader : shaders) {
		shader.dispose(device);
	}

	frameBuffers.create(device, swapChain, renderPass);

	VkDeviceSize bufferSize = sizeof(UniformBufferObject);
	for(size_t i = 0; i < uniformBuffers.size(); i++)
	{
		uniformBuffers[i].create(device, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		uniformBuffers[i].allocateMemory(device, physicalDevice, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	}

	descriptorSets.allocate(device, graphicsPipeline, swapChain.getImages().size());
	descriptorSets.configureDescriptors(device, uniformBuffers);

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

	// destroy graphics pipeline (and pipeline layout, descriptor set layout, descriptor pool)
	graphicsPipeline.dispose(device);

	// destroy render pass
	renderPass.dispose(device);

	// destroy swap chain (and image views)
	swapChain.dispose(device);

	// destroy uniform buffers
	for(size_t i = 0; i < uniformBuffers.size(); i++)
	{
		uniformBuffers[i].dispose(device);
	}
}

void Renderer::drawFrame()
{
	// fence waits for available frame
	vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	// semaphores to signal that an image has been acquired and is ready for rendering
	//		  and to signal that rendering has finished and presentation can happen
	VkSemaphore& waitSemaphore = imageAvailableSemaphores[currentFrame];
	VkSemaphore& signalSemaphore = renderFinishedSemaphores[currentFrame];
	VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

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

	// 
	updateUniformBuffer(imageIndex);

	// submit the command buffer
	commandBuffers[imageIndex].submit(device.getGraphicsQueue(), waitStage, waitSemaphore, signalSemaphore, inFlightFences[currentFrame]);

	// submit the result back to the swap chain to have it show up on the screen
	result = swapChain.queuePresentation(device.getPresentationQueue(), &imageIndex, signalSemaphore);
	if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized)
	{	// also recreate the swap chain if it is suboptimal
		recreateSwapChain();
		framebufferResized = false;
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Renderer::updateUniformBuffer(uint32_t currentImage)
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	UniformBufferObject ubo = {};
	ubo.model = Transformation::rotate(Matrix4(1.0f), time * glm::radians(90.0f), Vector3(0.0f, 0.0f, 1.0f));
	ubo.view = Transformation::lookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3::zero, Vector3::forward);
	ubo.proj = Transformation::perspective(glm::radians(45.0f), swapChain.getExtent().width / (float)swapChain.getExtent().height, 0.1f, 10.0f);
	ubo.proj[1][1] *= -1;

	uniformBuffers[currentImage].update(device, &ubo);
}
