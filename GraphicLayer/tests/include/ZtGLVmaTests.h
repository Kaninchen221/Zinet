#pragma once

#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

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
		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(renderer);

		const Instance& instance = renderer.getInstance();
		ASSERT_EQ(*instance.getInternal(), vk::Instance(allocatorCreateInfo.instance));
		ASSERT_EQ(*renderer.getDevice().getInternal(), vk::Device(allocatorCreateInfo.device));
		ASSERT_EQ(*renderer.getPhysicalDevice().getInternal(), vk::PhysicalDevice(allocatorCreateInfo.physicalDevice));

		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		ASSERT_EQ(applicationInfo.apiVersion, allocatorCreateInfo.vulkanApiVersion);
	}

	TEST_F(VmaTests, Create)
	{
		Renderer renderer;
		renderer.initialize();
		VmaAllocatorCreateInfo allocatorCreateInfo = vma.createAllocatorCreateInfo(renderer);
		vma.create(allocatorCreateInfo);

		const VmaAllocator vmaAllocator = vma.getInternal();
		ASSERT_NE(vmaAllocator, nullptr);
	}
}
