#pragma once

#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class PhysicalDeviceTests : public ::testing::Test
	{
	protected:

		PhysicalDevice physicalDevice;

	};

	TEST_F(PhysicalDeviceTests, GetInternalTest)
	{
		const vk::raii::PhysicalDevice& internal = physicalDevice.getInternal();
	}

	TEST_F(PhysicalDeviceTests, PickQueueFamilyIndexTest)
	{
		Instance instance;
		Context context;
		instance.createInstance(context);
		PhysicalDevice physicalDevice = instance.pickPhysicalDevice();
		uint32_t queueFamilyIndex = physicalDevice.pickQueueFamilyIndex();
		constexpr uint32_t notExpectedIndex = std::numeric_limits<uint32_t>::max();

		ASSERT_NE(queueFamilyIndex, notExpectedIndex);
	}

	TEST_F(PhysicalDeviceTests, CreateFeaturesTest)
	{
		physicalDevice.createFeatures();
	}

	TEST_F(PhysicalDeviceTests, GetFeaturesTest)
	{
		physicalDevice.createFeatures();
		const vk::PhysicalDeviceFeatures& physicalDeviceFeatures = physicalDevice.getFeatures();
	}
}