#pragma once

#include "Zinet/GraphicLayer/ZtGLRendererPipeline.h"

#include <gtest/gtest.h>


namespace zt::gl::tests
{

	class RendererPipelineSimpleTests : public ::testing::Test
	{
	protected:

		RendererPipeline rendererPipeline;

	};

	TEST(RendererPipelineSimpleTests, GetShadersModules)
	{
		typedef const std::vector<ShaderModule>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getShadersModules);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		const std::vector<ShaderModule>& shadersModules = rendererPipeline.getShadersModules();
		ASSERT_TRUE(shadersModules.empty());
	}

	TEST(RendererPipelineSimpleTests, GetShadersStages)
	{
		typedef const std::vector<vk::PipelineShaderStageCreateInfo>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getShadersStages);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
		
		RendererPipeline rendererPipeline;
		const std::vector<vk::PipelineShaderStageCreateInfo>& shadersStages = rendererPipeline.getShadersStages();
		ASSERT_TRUE(shadersStages.empty());
	}

	TEST(RendererPipelineSimpleTests, GetBindings)
	{
		typedef const std::vector<vk::DescriptorSetLayoutBinding>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getBindings);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		const std::vector<vk::DescriptorSetLayoutBinding>& bindings = rendererPipeline.getBindings();
		ASSERT_TRUE(bindings.empty());
	}

	TEST(RendererPipelineSimpleTests, GetDescriptorSetLayouts)
	{
		typedef const std::vector<DescriptorSetLayout>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getDescriptorSetLayouts);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		const std::vector<DescriptorSetLayout>& descriptorSetLayouts = rendererPipeline.getDescriptorSetLayouts();
		ASSERT_TRUE(descriptorSetLayouts.empty());
	}

	TEST(RendererPipelineSimpleTests, GetDescriptorSets)
	{
		typedef const std::optional<DescriptorSets>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getDescriptorSets);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		const std::optional<DescriptorSets>& descriptorSets = rendererPipeline.getDescriptorSets();
		ASSERT_FALSE(descriptorSets.has_value());
	}

	TEST(RendererPipelineSimpleTests, GetDescriptorPool)
	{
		typedef const DescriptorPool& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getDescriptorPool);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		[[maybe_unused]] const DescriptorPool& descriptorPool = rendererPipeline.getDescriptorPool();
	}

	TEST(RendererPipelineSimpleTests, GetDescriptorBufferInfos)
	{
		typedef const std::vector<vk::DescriptorBufferInfo>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getDescriptorBufferInfos);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		const std::vector<vk::DescriptorBufferInfo>& descriptorBufferInfos = rendererPipeline.getDescriptorBufferInfos();
		ASSERT_TRUE(descriptorBufferInfos.empty());
	}

	TEST(RendererPipelineSimpleTests, GetDescriptorImageInfos)
	{
		typedef const std::vector<vk::DescriptorImageInfo>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getDescriptorImageInfos);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		const std::vector<vk::DescriptorImageInfo>& descriptorImageInfos = rendererPipeline.getDescriptorImageInfos();
		ASSERT_TRUE(descriptorImageInfos.empty());
	}

	TEST(RendererPipelineSimpleTests, GetWriteDescriptorSets)
	{
		typedef const std::vector<vk::WriteDescriptorSet>& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getWriteDescriptorSets);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		const std::vector<vk::WriteDescriptorSet>& writeDescriptorSets = rendererPipeline.getWriteDescriptorSets();
		ASSERT_TRUE(writeDescriptorSets.empty());
	}

	TEST(RendererPipelineSimpleTests, GetPipelineLayout)
	{
		typedef const PipelineLayout& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getPipelineLayout);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		[[maybe_unused]] const PipelineLayout& pipelineLayout = rendererPipeline.getPipelineLayout();
	}

	TEST(RendererPipelineSimpleTests, GetPipeline)
	{
		typedef const Pipeline& (RendererPipeline::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&RendererPipeline::getPipeline);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		RendererPipeline rendererPipeline;
		[[maybe_unused]] const Pipeline& pipeline = rendererPipeline.getPipeline();
	}
}
