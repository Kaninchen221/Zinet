#pragma once

#include "Zinet/GraphicLayer/ZtGLVma.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class VmaTests : public ::testing::Test
	{
	protected:

		Vma vma;

	};

	TEST_F(VmaTests, GetInternal)
	{
		[[maybe_unused]] const VmaAllocator vmaAllocator = vma.getInternal();
	}

	TEST_F(VmaTests, CreateAllocatorCreateInfo)
	{
		Renderer renderer;
		renderer.initialize();
		RendererContext& rendererContext = renderer.getRendererContext();

		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(
			rendererContext.getInstance(), rendererContext.getDevice(), rendererContext.getPhysicalDevice());

		const Instance& instance = rendererContext.getInstance();
		ASSERT_EQ(*instance.getInternal(), vk::Instance(allocatorCreateInfo.instance));
		ASSERT_EQ(*rendererContext.getDevice().getInternal(), vk::Device(allocatorCreateInfo.device));
		ASSERT_EQ(*rendererContext.getPhysicalDevice().getInternal(), vk::PhysicalDevice(allocatorCreateInfo.physicalDevice));

		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		ASSERT_EQ(applicationInfo.apiVersion, allocatorCreateInfo.vulkanApiVersion);
	}

	TEST_F(VmaTests, Create)
	{
		Renderer renderer;
		renderer.initialize();
		RendererContext& rendererContext = renderer.getRendererContext();

		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(
			rendererContext.getInstance(), rendererContext.getDevice(), rendererContext.getPhysicalDevice());
		vma.create(allocatorCreateInfo);

		const VmaAllocator vmaAllocator = vma.getInternal();
		ASSERT_NE(vmaAllocator, nullptr);
	}
}
