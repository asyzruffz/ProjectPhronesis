#pragma once

#include <vulkan/vulkan.h>

namespace Phronesis
{
	class LogicalDevice;
	class Pipeline;
	class UniformBuffer;

	class DescriptorSets
	{
	public:
		DescriptorSets() = default;

		const std::vector<VkDescriptorSet>& getDescriptorSets() const;
		VkDescriptorSet& operator[](const size_t i);
		const size_t size() const;

		void allocate(const LogicalDevice& device, const Pipeline& pipeline, unsigned int count);

		void configureDescriptors(const LogicalDevice& device, const std::vector<UniformBuffer>& uniformBuffers);

	private:
		std::vector<VkDescriptorSet> descriptorSets;
	};
}
