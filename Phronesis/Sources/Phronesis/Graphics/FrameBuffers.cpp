
#include "StdAfx.hpp"
#include "FrameBuffers.hpp"

#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

const std::vector<VkFramebuffer>& FrameBuffers::getFrameBuffers() const
{
	return frameBuffers;
}

VkFramebuffer& FrameBuffers::operator[](const size_t i)
{
	return frameBuffers[i];
}

const size_t FrameBuffers::size() const
{
	return frameBuffers.size();
}

void FrameBuffers::create(const LogicalDevice& device, const SwapChain& swapChain, const RenderPass& renderPass)
{
	frameBuffers.resize(swapChain.getImageViews().size());

	for(size_t i = 0; i < swapChain.getImageViews().size(); i++)
	{
		VkImageView attachments[] = {
			swapChain.getImageViews()[i]
		};

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapChain.getExtent().width;
		framebufferInfo.height = swapChain.getExtent().height;
		framebufferInfo.layers = 1;

		VkResult result = vkCreateFramebuffer(device, &framebufferInfo, nullptr, &frameBuffers[i]);
		if(result != VK_SUCCESS)
		{
			Log::error("[Vulkan] Failed to create framebuffer");
			RenderUtils::checkVk(result);
		}
	}
}

void FrameBuffers::dispose(const LogicalDevice& device)
{
	for(auto frameBuffer : frameBuffers)
	{
		vkDestroyFramebuffer(device, frameBuffer, nullptr);
	}
}
