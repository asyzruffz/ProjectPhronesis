#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;

	class Shader
	{
	public:
		Shader();

		void create(const LogicalDevice& device, const std::string& filePath);
		void dispose(const LogicalDevice& device);

		const VkShaderModule& getModule() const;
		const VkShaderStageFlagBits& getStage() const;
		const VkPipelineShaderStageCreateInfo& getStageInfo() const;
		const std::vector<VkDescriptorSetLayoutBinding>& getDescriptorSetLayouts() const;

		static VkDescriptorSetLayoutBinding createDescriptorSetLayout(const uint32_t& binding, const VkDescriptorType& descriptorType, const VkShaderStageFlags& stage);

	private:
		void createShaderModule(const LogicalDevice& device, const std::vector<char>& code);
		void determineShaderStage(const std::string& filePath);
		void createShaderStageCreateInfo();

	private:
		VkShaderModule module;
		VkShaderStageFlagBits shaderStage;
		VkPipelineShaderStageCreateInfo shaderStageInfo;
		std::vector<VkDescriptorSetLayoutBinding> descriptorSetLayouts;
	};
}
