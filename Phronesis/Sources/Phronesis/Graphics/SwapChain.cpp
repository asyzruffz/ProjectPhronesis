
#include "StdAfx.hpp"
#include "SwapChain.hpp"

#include "Phronesis/Core.hpp"
#include "Window.hpp"
#include "LogicalDevice.hpp"
#include "Surface.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

SwapChain::SwapChain() :
	swapChain(VK_NULL_HANDLE)
{
}

SwapChain::operator const VkSwapchainKHR&() const
{
	return swapChain;
}

const VkSwapchainKHR& SwapChain::getSwapChain() const
{
	return swapChain;
}

void SwapChain::create(const LogicalDevice& device, const Surface& surface)
{
	auto capabilities = surface.getCapabilities();
	auto formats = surface.getFormats();
	auto presentationModes = surface.getPresentationModes();

	auto surfaceFormat = chooseSurfaceFormat(formats);
	auto presentationMode = choosePresentMode(presentationModes);
	extent = chooseExtent(capabilities);

	// request at least one more image because we may sometimes have to wait on the driver 
	// to complete internal operations before we can acquire another image to render to
	unsigned int imageCount = capabilities.minImageCount + 1;
	// make sure to not exceed the maximum number of images
	if(capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
	{ // 0  means that there is no maximum
		imageCount = capabilities.maxImageCount;
	}

	unsigned int queueFamilyIndices[] = {
		device.getGraphicsFamily(),
		device.getPresentationFamily()
	};

	// create the swap chain
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1; // always 1 unless we are developing a stereoscopic 3D application
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // render directly to image without post-processing
	if(device.getGraphicsFamily() != device.getPresentationFamily())
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	createInfo.preTransform = capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // blending with other windows in the window system? no, so opaque
	createInfo.presentMode = presentationMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create swap chain");
		RenderUtils::checkVk(result);
	}

	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	images.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, images.data());

	imageFormat = surfaceFormat.format;
	
	createImageViews(device);
}

void SwapChain::dispose(const LogicalDevice& device)
{
	for(auto imageView : imageViews)
	{
		vkDestroyImageView(device, imageView, nullptr);
	}

	vkDestroySwapchainKHR(device, swapChain, nullptr);
}

const VkExtent2D& SwapChain::getExtent() const
{
	return extent;
}

const std::vector<VkImage>& SwapChain::getImages() const
{
	return images;
}

const std::vector<VkImageView>& SwapChain::getImageViews() const
{
	return imageViews;
}

const VkFormat& SwapChain::getImageFormat() const
{
	return imageFormat;
}

VkSurfaceFormatKHR SwapChain::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	// VkSurfaceFormatKHR struct contains a format and a colorSpace member

	// VK_FORMAT_B8G8R8A8_UNORM means that we store the B, G, R and alpha channels in that order 
	// with an 8 bit unsigned integer for a total of 32 bits per pixel
	// VK_COLOR_SPACE_SRGB_NONLINEAR_KHR flag indicates if the SRGB color space is supported or not

	// best case scenario is that the surface has no preferred format
	if(availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	// if we're not free to choose any format, then we'll go through the list 
	// and see if the preferred combination is available
	for(const auto& availableFormat : availableFormats)
	{
		if(availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}

	// settle with the first format that is specified
	return availableFormats[0];
}

VkPresentModeKHR SwapChain::choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	// see the links to read about each presentation mode 
	// https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain#page_Presentation_mode

	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for(const auto& availablePresentMode : availablePresentModes)
	{
		if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
		else if(availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
		{
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}

VkExtent2D SwapChain::chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	// swap extent is the resolution of the swap chain images and 
	// it's almost always exactly equal to the resolution of the window that we're drawing to.
	// however, some window managers do allow us to differ by setting the width/height value 
	// to the maximum value of uint32_t

	auto window = Engine::Get()->getGame().getModule<Window>();

	if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		// pick the resolution that best matches the window
		auto windowSize = window->getSize();
		VkExtent2D actualExtent = { windowSize.x, windowSize.y };

		// clamp the value between the allowed minimum and maximum extents
		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

void SwapChain::createImageViews(const LogicalDevice& device)
{
	imageViews.resize(images.size());

	for(size_t i = 0; i < images.size(); i++)
	{
		// create image view
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = images[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D; // allows us to treat images as 1D, 2D, 3D textures or cube maps
		createInfo.format = imageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // used as color targets
		createInfo.subresourceRange.baseMipLevel = 0; // without any mipmapping levels
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1; // no multiple layers

		VkResult result = vkCreateImageView(device, &createInfo, nullptr, &imageViews[i]);
		if(result != VK_SUCCESS)
		{
			Log::error("[Vulkan] Failed to create image view");
			RenderUtils::checkVk(result);
		}
	}
}
