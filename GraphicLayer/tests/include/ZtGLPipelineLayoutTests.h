#pragma once

#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLDescriptorSetLayout.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class PipelineLayoutTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		PipelineLayout pipelineLayout;

		void SetUp() override
		{
			GLFW::Init();

			window.create();
			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.getRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);

			pipelineLayout.create(device);
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}

	};

	TEST(PipelineLayout, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<PipelineLayout, VulkanObject<vk::raii::PipelineLayout>>);
	}

	TEST(PipelineLayout, DefaultViewport)
	{
		PipelineLayout pipelineLayout;

		vk::Viewport expected;
		expected.x = 0.0f;
		expected.y = 0.0f;
		expected.width = 100.f;
		expected.height = 100.f;
		expected.minDepth = 0.0f;
		expected.maxDepth = 1.0f;

		const vk::Viewport& actual = pipelineLayout.getViewport();

		ASSERT_EQ(expected, actual);
	}

	TEST(PipelineLayout, DefaultScissor)
	{
		PipelineLayout pipelineLayout;

		vk::Rect2D expected;
		expected.offset = vk::Offset2D{ 0, 0 };
		expected.extent = vk::Extent2D{ 0, 0 };

		const vk::Rect2D& actual = pipelineLayout.getScissor();

		ASSERT_EQ(expected, actual);
	}

	TEST(PipelineLayout, CreateShaderStageCreateInfo)
	{
		PipelineLayout pipelineLayout;

		ShaderModule shaderModule;
		vk::PipelineShaderStageCreateInfo createInfo = pipelineLayout.createShaderStageCreateInfo(shaderModule);

		ASSERT_NE(createInfo, vk::PipelineShaderStageCreateInfo{});
	}

	TEST(PipelineLayout, CreateVertexInputStateCreateInfo)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineVertexInputStateCreateInfo createInfo = pipelineLayout.createVertexInputStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineVertexInputStateCreateInfo{});
	}
	
	TEST(PipelineLayout, CreateInputAssemblyStateCreateInfo)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineInputAssemblyStateCreateInfo createInfo = pipelineLayout.createInputAssemblyStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineInputAssemblyStateCreateInfo{});
	}

	TEST(PipelineLayout, SetViewportSize)
	{
		PipelineLayout pipelineLayout;

		vk::Viewport expected = pipelineLayout.getViewport();
		expected.width = 200.f;
		expected.height = 200.f;

		pipelineLayout.setViewportSize(expected.width, expected.height);
		const vk::Viewport& actual = pipelineLayout.getViewport();

		ASSERT_EQ(expected, actual);
	}
	
	TEST(PipelineLayout, GetViewport)
	{
		PipelineLayout pipelineLayout;
		const vk::Viewport& actual = pipelineLayout.getViewport();
	}

	TEST(PipelineLayout, GetScissor)
	{
		PipelineLayout pipelineLayout;
		const vk::Rect2D& scissor = pipelineLayout.getScissor();
	}

	TEST(PipelineLayout, SetScissor)
	{
		PipelineLayout pipelineLayout;

		vk::Rect2D expected;
		expected.offset = vk::Offset2D{ 23, 566 };
		expected.extent = vk::Extent2D{ 100, 200 };
		pipelineLayout.setScissor(expected);

		const vk::Rect2D& actual = pipelineLayout.getScissor();

		ASSERT_EQ(expected, actual);
	}

	TEST(PipelineLayout, CreateViewportStateCreateInfo)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineViewportStateCreateInfo createInfo = pipelineLayout.createViewportStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineViewportStateCreateInfo{});
	}

	TEST(PipelineLayout, CreateRasterizationStateCreateInfo)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineRasterizationStateCreateInfo createInfo = pipelineLayout.createRasterizationStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineRasterizationStateCreateInfo{});
	}

	TEST(PipelineLayout, CreateMultisampleStateCreateInfo)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineMultisampleStateCreateInfo createInfo = pipelineLayout.createMultisampleStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineMultisampleStateCreateInfo{});
	}

	TEST(PipelineLayout, CreateColorBlendAttachmentState)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineColorBlendAttachmentState createInfo = pipelineLayout.createColorBlendAttachmentState();

		ASSERT_NE(createInfo, vk::PipelineColorBlendAttachmentState{});
	}

	TEST(PipelineLayout, CreateColorBlendStateCreateInfo)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineColorBlendStateCreateInfo createInfo = pipelineLayout.createColorBlendStateCreateInfo();

		ASSERT_NE(createInfo, vk::PipelineColorBlendStateCreateInfo{});
	}

	TEST(PipelineLayout, CreatePipelineLayoutCreateInfo)
	{
		PipelineLayout pipelineLayout;

		vk::PipelineLayoutCreateInfo createInfo = pipelineLayout.createPipelineLayoutCreateInfo();

		ASSERT_EQ(createInfo.setLayoutCount, 1);
		ASSERT_EQ(createInfo.pSetLayouts, &(*pipelineLayout.getDescriptorSetLayout().getInternal()));
		ASSERT_EQ(createInfo.pushConstantRangeCount, 0);
		ASSERT_EQ(createInfo.pPushConstantRanges, nullptr);
	}

	TEST(PipelineLayout, GetPipelineLayout)
	{
		PipelineLayout pipelineLayout;

		ASSERT_EQ(*pipelineLayout.getInternal(), *vk::raii::PipelineLayout{ std::nullptr_t{} });
	}

	TEST(PipelineLayout, GetDescriptorSetLayout)
	{
		PipelineLayout pipelineLayout;
		const DescriptorSetLayout& descriptorSetLayout = pipelineLayout.getDescriptorSetLayout();
	}

	TEST_F(PipelineLayoutTests, CreatePipelineLayout)
	{
		ASSERT_NE(*pipelineLayout.getInternal(), *vk::raii::PipelineLayout{ std::nullptr_t{} });
	}
}