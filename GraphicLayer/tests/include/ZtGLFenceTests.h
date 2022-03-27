#pragma once

#include "Zinet/GraphicLayer/ZtGLFence.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class FenceTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Fence fence;

		void SetUp() override
		{
			GLFW::InitGLFW();

			instance.createInstanceCreateInfo();
			instance.create(context);

			window.createWindow();

			surface.create(instance, window);

			physicalDevice.create(instance);

			device.create(physicalDevice, surface);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(Fence, GetInternalTest)
	{
		Fence fence;
		vk::raii::Fence& internal = fence.getInternal();

		ASSERT_EQ(*internal, *vk::raii::Fence{ std::nullptr_t{} });
	}

	TEST(Fence, CreateFenceCreateInfoTest)
	{
		Fence fence;
		vk::FenceCreateInfo createInfo = fence.createFenceCreateInfo();

		ASSERT_NE(createInfo, vk::FenceCreateInfo{});
	}

	TEST_F(FenceTests, CreateTest)
	{
		fence.create(device);

		ASSERT_NE(*fence.getInternal(), *vk::raii::Fence{ std::nullptr_t{} });
	}

	TEST_F(FenceTests, GetStatusTest)
	{
		fence.create(device);
		vk::Result result = fence.getStatus();

		ASSERT_EQ(result, vk::Result::eSuccess);
	}
}
