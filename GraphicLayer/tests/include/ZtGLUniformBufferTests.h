#pragma once

#include "Zinet/GraphicLayer/ZtGLUniformBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class UniformBufferTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		UniformBuffer uniformBuffer;

		void SetUp() override
		{
			GLFW::InitGLFW();

			window.create();
			instance.createApplicationInfo();
			instance.createInstanceCreateInfo();
			instance.create(context);
			surface.create(instance, window);
			physicalDevice.create(instance);
			device.create(physicalDevice, surface);

			uniformBuffer.setSize(1u);
			vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo();
			uniformBuffer.create(device, uniformBufferCreateInfo);
		}

		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(UniformBuffer, DerivedFromBuffer)
	{
		static_assert(std::derived_from<UniformBuffer, Buffer>);
	}

	TEST(UniformBuffer, CreateCreateInfo)
	{
		UniformBuffer uniformBuffer;
		vk::BufferCreateInfo uniformBufferCreateInfo = uniformBuffer.createCreateInfo();

		ASSERT_EQ(uniformBufferCreateInfo.usage, vk::BufferUsageFlagBits::eUniformBuffer);
		ASSERT_EQ(uniformBufferCreateInfo.size, uniformBuffer.getSize());
		ASSERT_EQ(uniformBufferCreateInfo.sharingMode, vk::SharingMode::eExclusive);
	}

	TEST_F(UniformBufferTests, CreateTest)
	{
		ASSERT_NE(*uniformBuffer.getInternal(), *vk::raii::Buffer{ std::nullptr_t{} });
	}

}