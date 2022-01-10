#pragma once

#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class PhysicalDeviceTests : public ::testing::Test
	{
	protected:

		PhysicalDevice physicalDeviceHelper;

	};

	TEST_F(PhysicalDeviceTests, PickQueueFamilyIndex)
	{
		Instance instance;
		Context context;
		instance.createInstance(context);
		vk::raii::PhysicalDevice physicalDevice = instance.pickPhysicalDevice();
		uint32_t queueFamilyIndex = physicalDeviceHelper.pickQueueFamilyIndex(physicalDevice);
		constexpr uint32_t notExpectedIndex = std::numeric_limits<uint32_t>::max();

		ASSERT_NE(queueFamilyIndex, notExpectedIndex);
	}

	TEST_F(PhysicalDeviceTests, CreatePhysicalDeviceFeatures)
	{
		vk::PhysicalDeviceFeatures physicalDeviceFeatures = physicalDeviceHelper.createPhysicalDeviceFeatures();
	}
}