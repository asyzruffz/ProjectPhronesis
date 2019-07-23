
#include "StdAfx.hpp"
#include "GraphicsPipeline.hpp"

#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "Shader.hpp"
#include "RenderPass.hpp"
#include "Vertex.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

GraphicsPipeline::GraphicsPipeline()
{
	pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
}

void GraphicsPipeline::create(const LogicalDevice& device, const SwapChain& swapChain, const std::vector<Shader>& shaders, const RenderPass& renderPass)
{
	createDescriptorSetLayout(device, shaders[1]); // TODO: better way to choose vertex shader
	createDescriptorPool(device, shaders[1], static_cast<unsigned int>(swapChain.getImages().size()));
	createPipelineLayout(device);

	// get shader stages
	std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
	shaderStages.resize(shaders.size());
	for(size_t i = 0; i < shaders.size(); i++)
	{
		shaderStages[i] = shaders[i].getStageInfo();
	}

	// create vertex input (describes the format of the vertex data that will be passed to the vertex shader)
	auto bindingDescription = Vertex::getBindingDescription();
	auto attributeDescriptions = Vertex::getAttributeDescriptions();

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	// create input assembly (describes what kind of geometry will be drawn from the vertices)
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)swapChain.getExtent().width;
	viewport.height = (float)swapChain.getExtent().height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChain.getExtent();

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
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE; // specifies the vertex order (technically VK_FRONT_FACE_CLOCKWISE but reversed by Y-flip in the projection matrix)
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

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
	pipelineInfo.pStages = shaderStages.data();
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr; // Optional
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = nullptr; // Optional
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional

	VkResult result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create graphics pipeline");
		RenderUtils::checkVk(result);
	}
}
