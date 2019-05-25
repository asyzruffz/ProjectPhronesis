
#include "StdAfx.hpp"
#include "RenderUtils.hpp"

#include "Phronesis/Core/Game.hpp"
#include "Instance.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace Phronesis;

void RenderUtils::checkVk(const VkResult &result)
{
	// check the result and throw exceptions if unsuccessful
	if (result >= 0)
	{
		return; // no error
	}

	std::string failure = stringifyResultVk(result);
	throw std::runtime_error("[ERROR] [Vulkan] " + failure);
}

std::string RenderUtils::stringifyResultVk(const VkResult &result)
{
	switch (result)
	{
	case VK_SUCCESS:
		return "Success";
	case VK_NOT_READY:
		return "A fence or query has not yet completed";
	case VK_TIMEOUT:
		return "A wait operation has not completed in the specified time";
	case VK_EVENT_SET:
		return "An event is signaled";
	case VK_EVENT_RESET:
		return "An event is unsignaled";
	case VK_INCOMPLETE:
		return "A return array was too small for the result";
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		return "A host memory allocation has failed";
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		return "A device memory allocation has failed";
	case VK_ERROR_INITIALIZATION_FAILED:
		return "Initialization of an object could not be completed for implementation-specific reasons";
	case VK_ERROR_DEVICE_LOST:
		return "The logical or physical device has been lost";
	case VK_ERROR_MEMORY_MAP_FAILED:
		return "Mapping of a memory object has failed";
	case VK_ERROR_LAYER_NOT_PRESENT:
		return "A requested layer is not present or could not be loaded";
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		return "A requested extension is not supported";
	case VK_ERROR_FEATURE_NOT_PRESENT:
		return "A requested feature is not supported";
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible";
	case VK_ERROR_TOO_MANY_OBJECTS:
		return "Too many objects of the type have already been created";
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		return "A requested format is not supported on this device";
	case VK_ERROR_SURFACE_LOST_KHR:
		return "A surface is no longer available";
//	case VK_ERROR_OUT_OF_POOL_MEMORY:
//		return "A allocation failed due to having no more space in the descriptor pool";
	case VK_SUBOPTIMAL_KHR:
		return "A swapchain no longer matches the surface properties exactly, but can still be used";
	case VK_ERROR_OUT_OF_DATE_KHR:
		return "A surface has changed in such a way that it is no longer compatible with the swapchain";
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		return "The display used by a swapchain does not use the same presentable image layout";
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API";
	case VK_ERROR_VALIDATION_FAILED_EXT:
		return "A validation layer found an error";
	default:
		return "Unknown Vulkan error " + std::to_string(result);
	}
}

std::string RenderUtils::stringifyMessageSeverity(const VkDebugUtilsMessageSeverityFlagBitsEXT &severity)
{
	switch(severity)
	{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			return "VERBOSE";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			return "INFO";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			return "WARNING";
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			return "ERROR";
		default:
			return "?";
	}
}

VkSurfaceFormatKHR RenderUtils::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
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

VkPresentModeKHR RenderUtils::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
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

VkExtent2D RenderUtils::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window)
{
	// swap extent is the resolution of the swap chain images and 
	// it's almost always exactly equal to the resolution of the window that we're drawing to.
	// however, some window managers do allow us to differ by setting the width/height value 
	// to the maximum value of uint32_t

	if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		// pick the resolution that best matches the window
		VkExtent2D actualExtent = { 
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		// clamp the value between the allowed minimum and maximum extents
		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

VkShaderModule RenderUtils::createShaderModule(VkDevice device, const std::vector<char>& code)
{
	// create shader module
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create shader module");
		checkVk(result);
	}

	return shaderModule;
}
