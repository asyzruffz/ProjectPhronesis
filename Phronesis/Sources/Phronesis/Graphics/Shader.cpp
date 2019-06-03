
#include "StdAfx.hpp"
#include "Shader.hpp"

#include "Phronesis/FileIO/BinaryFile.hpp"
#include "Phronesis/Utilities/String.hpp"
#include "LogicalDevice.hpp"
#include "RenderUtils.hpp"

using namespace Phronesis;

Shader::Shader() :
	module(VK_NULL_HANDLE),
	shaderStage(VK_SHADER_STAGE_ALL),
	shaderStageInfo({})
{
}

void Shader::create(const LogicalDevice& device, const std::string& filePath)
{
	// create shader module
	auto shaderCode = BinaryFile::read(filePath);
	createShaderModule(device, shaderCode);

	// create shader stages
	determineShaderStage(filePath);
	createShaderStageCreateInfo();

	// create descriptor set layout
	if(shaderStage & VK_SHADER_STAGE_VERTEX_BIT)
	{
		// ubo layout binding
		descriptorSetLayouts.emplace_back(createDescriptorSetLayout(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT));
	}
}

void Shader::dispose(const LogicalDevice& device)
{
	vkDestroyShaderModule(device, module, nullptr);
}

const VkShaderModule& Shader::getModule() const
{
	return module;
}

const VkShaderStageFlagBits& Shader::getStage() const
{
	return shaderStage;
}

const VkPipelineShaderStageCreateInfo& Shader::getStageInfo() const
{
	return shaderStageInfo;
}

const std::vector<VkDescriptorSetLayoutBinding>& Shader::getDescriptorSetLayouts() const
{
	return descriptorSetLayouts;
}

VkDescriptorSetLayoutBinding Shader::createDescriptorSetLayout(const uint32_t& binding, const VkDescriptorType& descriptorType, const VkShaderStageFlags& stage)
{
	VkDescriptorSetLayoutBinding descriptorSetLayoutBinding = {};
	descriptorSetLayoutBinding.binding = binding;
	descriptorSetLayoutBinding.descriptorCount = 1;
	descriptorSetLayoutBinding.descriptorType = descriptorType;
	descriptorSetLayoutBinding.stageFlags = stage;
	descriptorSetLayoutBinding.pImmutableSamplers = nullptr;
	return descriptorSetLayoutBinding;
}

void Shader::createShaderModule(const LogicalDevice& device, const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &module);
	if(result != VK_SUCCESS)
	{
		Log::error("[Vulkan] Failed to create shader module");
		RenderUtils::checkVk(result);
	}
}

void Shader::determineShaderStage(const std::string& filePath)
{
	std::string spvExt = std::filesystem::path(filePath).extension().string();
	std::string spvRemoved = filePath.substr(0, filePath.find(spvExt));
	std::string shaderExt = std::filesystem::path(spvRemoved).extension().string();
	
	shaderExt = String::lowercase(shaderExt);
	if(shaderExt == ".comp")
	{
		shaderStage = VK_SHADER_STAGE_COMPUTE_BIT;
		return;
	}
	if(shaderExt == ".vert")
	{
		shaderStage = VK_SHADER_STAGE_VERTEX_BIT;
		return;
	}
	if(shaderExt == ".tesc")
	{
		shaderStage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		return;
	}
	if(shaderExt == ".tese")
	{
		shaderStage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		return;
	}
	if(shaderExt == ".geom")
	{
		shaderStage = VK_SHADER_STAGE_GEOMETRY_BIT;
		return;
	}
	if(shaderExt == ".frag")
	{
		shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT;
		return;
	}

	shaderStage = VK_SHADER_STAGE_ALL;
}

void Shader::createShaderStageCreateInfo()
{
	shaderStageInfo = {};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageInfo.stage = shaderStage;
	shaderStageInfo.module = module;
	shaderStageInfo.pName = "main";
}
