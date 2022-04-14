#pragma once

#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class PipelineLayoutTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<PipelineLayout> pipeline = std::make_unique<PipelineLayout>();

	};

	TEST(PipelineLayout, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<PipelineLayout, VulkanObject<vk::raii::PipelineLayout>>);
	}

	TEST_F(PipelineLayoutTests, DefaultViewportTest)
	{
		vk::Viewport expected;
		expected.x = 0.0f;
		expected.y = 0.0f;
		expected.width = 100.f;
		expected.height = 100.f;
		expected.minDepth = 0.0f;
		expected.maxDepth = 1.0f;

		const vk::Viewport& actual = pipeline->getViewport();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(PipelineLayoutTests, DefaultScissorTest)
	{
		vk::Rect2D expected;
		expected.offset = vk::Offset2D{ 0, 0 };
		expected.extent = vk::Extent2D{ 0, 0 };

		const vk::Rect2D& actual = pipeline->getScissor();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(PipelineLayoutTests, CreateShaderStageCreateInfoTest)
	{
		ShaderModule shaderModule;
		vk::PipelineShaderStageCreateInfo createInfo = pipeline->createShaderStageCreateInfo(shaderModule);

		ASSERT_NE(createInfo, vk::PipelineShaderStageCreateInfo{});
	}

	TEST_F(PipelineLayoutTests, CreateVertexInputStateCreateInfoTest)
	{
		vk::PipelineVertexInputStateCreateInfo createInfo = pipeline->createVertexInputStateCreateInfo();

		ASSERT_EQ(createInfo, vk::PipelineVertexInputStateCreateInfo{});
	}
	
	TEST_F(PipelineLayoutTests, CreateInputAssemblyStateCreateInfoTest)
	{
		vk::PipelineInputAssemblyStateCreateInfo createInfo = pipeline->createInputAssemblyStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineInputAssemblyStateCreateInfo{});
	}

	TEST_F(PipelineLayoutTests, SetViewportSizeTest)
	{
		vk::Viewport expected = pipeline->getViewport();
		expected.width = 200.f;
		expected.height = 200.f;

		pipeline->setViewportSize(expected.width, expected.height);
		const vk::Viewport& actual = pipeline->getViewport();

		ASSERT_EQ(expected, actual);
	}
	
	TEST_F(PipelineLayoutTests, GetViewportTest)
	{	
		const vk::Viewport& actual = pipeline->getViewport();
	}

	TEST_F(PipelineLayoutTests, GetScissorTest)
	{
		const vk::Rect2D& scissor = pipeline->getScissor();
	}

	TEST_F(PipelineLayoutTests, SetScissorTest)
	{
		vk::Rect2D expected;
		expected.offset = vk::Offset2D{ 23, 566 };
		expected.extent = vk::Extent2D{ 100, 200 };
		pipeline->setScissor(expected);

		const vk::Rect2D& actual = pipeline->getScissor();

		ASSERT_EQ(expected, actual);
	}

	TEST_F(PipelineLayoutTests, CreateViewportStateCreateInfoTest)
	{
		vk::PipelineViewportStateCreateInfo createInfo = pipeline->createViewportStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineViewportStateCreateInfo{});
	}

	TEST_F(PipelineLayoutTests, CreateRasterizationStateCreateInfoTest)
	{
		vk::PipelineRasterizationStateCreateInfo createInfo = pipeline->createRasterizationStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineRasterizationStateCreateInfo{});
	}

	TEST_F(PipelineLayoutTests, CreateMultisampleStateCreateInfoTest)
	{
		vk::PipelineMultisampleStateCreateInfo createInfo = pipeline->createMultisampleStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineMultisampleStateCreateInfo{});
	}

	TEST_F(PipelineLayoutTests, CreateColorBlendAttachmentStateTest)
	{
		vk::PipelineColorBlendAttachmentState createInfo = pipeline->createColorBlendAttachmentState();

		ASSERT_NE(createInfo, vk::PipelineColorBlendAttachmentState{});
	}

	TEST_F(PipelineLayoutTests, CreateColorBlendStateCreateInfoTest)
	{
		vk::PipelineColorBlendStateCreateInfo createInfo = pipeline->createColorBlendStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineColorBlendStateCreateInfo{});
	}

	TEST_F(PipelineLayoutTests, CreatePipelineLayoutCreateInfoTest)
	{
		vk::PipelineLayoutCreateInfo createInfo = pipeline->createPipelineLayoutCreateInfo();

		ASSERT_EQ(createInfo, vk::PipelineLayoutCreateInfo{});
	}

	TEST_F(PipelineLayoutTests, GetPipelineLayoutTest)
	{
		vk::raii::PipelineLayout& pipelineLayout = pipeline->getInternal();

		ASSERT_EQ(*pipelineLayout, *vk::raii::PipelineLayout{ std::nullptr_t{} });
	}

	TEST_F(PipelineLayoutTests, CreatePipelineLayoutTest)
	{
		GLFW::InitGLFW();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Window window;
		window.create();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);
		Device device;
		device.create(physicalDevice, surface);

		pipeline->create(device);
		vk::raii::PipelineLayout& pipelineLayout = pipeline->getInternal();

		ASSERT_NE(*pipelineLayout, *vk::raii::PipelineLayout{ std::nullptr_t{} });

		pipeline.reset();

		GLFW::DeinitGLFW();
	}
}