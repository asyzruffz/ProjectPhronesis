
#include "Renderer.hpp"

#include <iostream>
#include <set>
#include <stdexcept>

#include "Phronesis/Graphics/RenderUtils.hpp"
#include "Phronesis/FileIO/BinaryFile.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace Phronesis;


#ifdef NDEBUG // means "not debug"
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

void Renderer::initWindow(int width, int height, const char* title)
{
	glfwInit(); // initialize the glfw library

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // tell it to not create an OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable window resize

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void Renderer::initVulkan()
{
	createInstance();
	setupDebugMessenger();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
	createSwapChain();
	createImageViews();
	createGraphicsPipeline();
}

void Renderer::update()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void Renderer::disposeVulkan()
{
	// destroy pipeline layout
	vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

	for(auto imageView : swapChainImageViews)
	{	// destroy image views
		vkDestroyImageView(device, imageView, nullptr);
	}
	vkDestroySwapchainKHR(device, swapChain, nullptr); // destroy swap chain
	vkDestroyDevice(device, nullptr); // destroy logical device (and queues)
	if (enableValidationLayers) 
	{	// destroy debug messenger resposible for validation
		RenderUtils::destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}
	vkDestroySurfaceKHR(instance, surface, nullptr); // destroy window surface
	vkDestroyInstance(instance, nullptr); // destroy Vulkan instance
}

void Renderer::disposeWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	//system("pause");
}

void Renderer::createInstance()
{
	if (enableValidationLayers && !RenderUtils::checkValidationLayerSupport()) {
		throw std::runtime_error("Vulkan error: Validation layers requested, but not available!");
	}

	// some information about our application
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Game";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Phronesis";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	auto extensions = getRequiredExtensions();

	// log the extensions
#ifndef NDEBUG
	// get a list of available extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensionsAvailable(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsAvailable.data());

	std::cout << "Vulkan info: Required extensions:" << std::endl;
	for (const auto& extension : extensions) {
		std::cout << "\t" << extension << std::endl;
	}

	std::cout << "Vulkan info: Available extensions:" << std::endl;
	for (const auto& extension : extensionsAvailable) {
		std::cout << "\t" << extension.extensionName << std::endl;
	}
#endif

	// function parameters for creating a Vulkan instance (not optional),
	// tells the Vulkan driver which global extensions and
	// validation layers we want to use
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(RenderUtils::validationLayers.size());
		createInfo.ppEnabledLayerNames = RenderUtils::validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	if(result != VK_SUCCESS)
	{
		std::cerr << "Vulkan error: Failed to create instance" << std::endl;
		RenderUtils::checkVk(result);
	}
}

void Renderer::setupDebugMessenger()
{
	if (!enableValidationLayers) return;

	// function parameters for creating debug messenger,
	// detailing the messages type and severity that will run callback 
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = RenderUtils::debugCallback;
	createInfo.pUserData = nullptr; // Optional

	VkResult result = RenderUtils::createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
	if (result != VK_SUCCESS) 
	{
		std::cerr << "Vulkan error: Failed to set up debug messenger" << std::endl;
		RenderUtils::checkVk(result);
	}
}

void Renderer::createSurface()
{
	VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
	if(result != VK_SUCCESS)
	{
		std::cerr << "Vulkan error: Failed to create window surface" << std::endl;
		RenderUtils::checkVk(result);
	}
}

void Renderer::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("Vulkan error: Failed to find GPUs with Vulkan support");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		if (RenderUtils::isDeviceSuitable(device, surface)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("Vulkan error: Failed to find a suitable GPU");
	}
}

void Renderer::createLogicalDevice()
{
	QueueFamilyIndices indices = RenderUtils::findQueueFamilies(physicalDevice, surface);

	// make sure the queue families are not redundant while making different queues
	std::set<uint32_t> uniqueQueueFamilies = { 
		indices.graphicsFamily.value(), 
		indices.presentationFamily.value() 
	};

	// vector to store the createinfos for each queue
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

	float queuePriority = 1.0f; // between 0.0 and 1.0
	for(uint32_t queueFamily : uniqueQueueFamilies)
	{
		// specifying details for logical device creation
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1; // the number of queues we want for a single queue family
		queueCreateInfo.pQueuePriorities = &queuePriority;

		queueCreateInfos.push_back(queueCreateInfo);

	}

	// specify is the set of device features that we'll be using.
	// features that needed to be queried support for with vkGetPhysicalDeviceFeatures 
	// in RenderUtils::isDeviceSuitable()
	VkPhysicalDeviceFeatures deviceFeatures = {};

	// creating the logical device
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(RenderUtils::deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = RenderUtils::deviceExtensions.data();
	if(enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(RenderUtils::validationLayers.size());
		createInfo.ppEnabledLayerNames = RenderUtils::validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
	if(result != VK_SUCCESS)
	{
		std::cerr << "Vulkan error: Failed to create logical device" << std::endl;
		RenderUtils::checkVk(result);
	}

	// the queues are automatically created along with the logical device,
	// but we need to have a handle to interface with the graphics and presentation queue
	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentationFamily.value(), 0, &presentationQueue);
}

void Renderer::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = RenderUtils::querySwapChainSupport(physicalDevice, surface);

	VkSurfaceFormatKHR surfaceFormat = RenderUtils::chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentationMode = RenderUtils::chooseSwapPresentMode(swapChainSupport.presentationModes);
	VkExtent2D extent = RenderUtils::chooseSwapExtent(swapChainSupport.capabilities);

	// request at least one more image because we may sometimes have to wait on the driver 
	// to complete internal operations before we can acquire another image to render to
	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	// make sure to not exceed the maximum number of images
	if(swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{ // 0  means that there is no maximum
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	QueueFamilyIndices indices = RenderUtils::findQueueFamilies(physicalDevice, surface);
	uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentationFamily.value() };

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
	if(indices.graphicsFamily != indices.presentationFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // blending with other windows in the window system? no, so opaque
	createInfo.presentMode = presentationMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
	if(result != VK_SUCCESS)
	{
		std::cerr << "Vulkan error: Failed to create swap chain" << std::endl;
		RenderUtils::checkVk(result);
	}

	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;
}

void Renderer::createImageViews()
{
	swapChainImageViews.resize(swapChainImages.size());

	for(size_t i = 0; i < swapChainImages.size(); i++)
	{
		// create image view
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D; // allows us to treat images as 1D, 2D, 3D textures or cube maps
		createInfo.format = swapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // used as color targets
		createInfo.subresourceRange.baseMipLevel = 0; // without any mipmapping levels
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1; // no multiple layers

		VkResult result = vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]);
		if(result != VK_SUCCESS)
		{
			std::cerr << "Vulkan error: Failed to create image view" << std::endl;
			RenderUtils::checkVk(result);
		}
	}
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

	// create vertex input (describes the format of the vertex data that will be passed to the vertex shader)
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

	// create input assembly (describes what kind of geometry will be drawn from the vertices)
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)swapChainExtent.width;
	viewport.height = (float)swapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;

	// create viewport state (note: using multiple requires enabling a GPU feature)
	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE; // useful in shadow maps if true (requires enabling a GPU feature)
	rasterizer.rasterizerDiscardEnable = VK_FALSE; // disables any output to the framebuffer if true
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL; // FILL, LINE, POINT (mode other than fill requires enabling a GPU feature)
	rasterizer.lineWidth = 1.0f; // line thicker than 1.0f requires you to enable the wideLines GPU feature
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT; // can disable culling, cull the front faces, cull the back faces or both
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE; // specifies the vertex order
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling = {}; // disabled for now
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE; // in our case we only have one framebuffer

	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pushConstantRangeCount = 0;

	VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);
	if(result != VK_SUCCESS)
	{
		std::cerr << "Vulkan error: Failed to create pipeline layout" << std::endl;
		RenderUtils::checkVk(result);
	}

	// destroy shader modules
	vkDestroyShaderModule(device, fragShaderModule, nullptr);
	vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

std::vector<const char*> Renderer::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	// GLFW built-in function returning the extension(s) required to 
	// interface with the window system
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	// extension to set up a debug messenger with a callback
	if (enableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}
