#pragma once

#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{
	class RenderStatesTests : public ::testing::Test
	{
	protected:

		RenderStates renderStates;

		static_assert(std::is_same_v<decltype(renderStates.shaders), std::span<Shader>>);
		static_assert(std::is_same_v<decltype(renderStates.descriptors), std::span<RenderStates::Descriptor>>);
		static_assert(std::is_same_v<decltype(renderStates.images), std::span<RenderStates::Image>>);
		static_assert(std::is_same_v<decltype(renderStates.modelMatrix), Matrix4f>);
		static_assert(std::is_same_v<decltype(renderStates.camera), const Camera&>);
	};

	class DrawInfoTests : public ::testing::Test
	{
	protected:

		DrawInfo drawInfo;

		static_assert(std::is_same_v<decltype(drawInfo.vertexBuffer), VertexBuffer>);
		static_assert(std::is_same_v<decltype(drawInfo.indexBuffer), IndexBuffer>);
		static_assert(std::is_same_v<decltype(drawInfo.indices), std::vector<std::uint16_t>>);
		static_assert(std::is_same_v<decltype(drawInfo.uniformBuffers), std::vector<UniformBuffer>>);
		static_assert(std::is_same_v<decltype(drawInfo.MVPBufferIndex), size_t>);
		static_assert(std::is_same_v<decltype(drawInfo.instanceCount), std::uint32_t>);
	};

	TEST_F(DrawInfoTests, DefaultValues)
	{
		EXPECT_EQ(drawInfo.MVPBufferIndex, std::numeric_limits<size_t>::max());
		EXPECT_EQ(drawInfo.instanceCount, 1u);
	}

	class DescriptorInfoTests : public ::testing::Test
	{
	protected:

		RenderStates::Descriptor descriptor;

		static_assert(std::is_same_v<decltype(descriptor.binding), std::uint32_t>);
		static_assert(std::is_same_v<decltype(descriptor.descriptorType), DescriptorType>);
		static_assert(std::is_same_v<decltype(descriptor.count), std::uint32_t>);
		static_assert(std::is_same_v<decltype(descriptor.shaderType), ShaderType>);
	};

	TEST_F(DescriptorInfoTests, Properties)
	{
		ASSERT_EQ(descriptor.binding, 0u);
		ASSERT_EQ(descriptor.count, 0u);
	}

	TEST_F(DescriptorInfoTests, ToVkDescriptorSetLayoutBinding)
	{
		descriptor.binding = 4u;
		descriptor.descriptorType = DescriptorType::eUniformBuffer;
		descriptor.count = 2u;
		descriptor.shaderType = ShaderType::Vertex;

		vk::DescriptorSetLayoutBinding vkBinding = descriptor.toVkDescriptorSetLayoutBinding();

		ASSERT_EQ(vkBinding.binding, 4u);
		ASSERT_EQ(vkBinding.descriptorType, DescriptorType::eUniformBuffer);
		ASSERT_EQ(vkBinding.descriptorCount, 2u);
		ASSERT_EQ(vkBinding.stageFlags, ShaderTypeToVkShaderStage(ShaderType::Vertex));
	}

	class ImageInfoTests : public ::testing::Test
	{
	protected:

		ImageBuffer buffer;
		Sampler sampler;
		ImageView imageView;
		RenderStates::Image image{ buffer, sampler, imageView, vk::ImageLayout{} };

	};

	TEST_F(ImageInfoTests, Properties)
	{
		static_assert(std::is_same_v<decltype(image.buffer), const ImageBuffer&>);
		static_assert(std::is_same_v<decltype(image.sampler), const Sampler&>);
		static_assert(std::is_same_v<decltype(image.view), const ImageView&>);
		static_assert(std::is_same_v<decltype(image.layout), vk::ImageLayout>);
	}
}
