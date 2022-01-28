#pragma once

#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class InstanceTests : public ::testing::Test
	{
	protected:

		Instance instance;

	};

	TEST_F(InstanceTests, InternalTest)
	{
		const vk::raii::Instance& internal = instance.getInternal();
	}

	TEST_F(InstanceTests, ApplicationInfoTest)
	{
		instance.createApplicationInfo();
		const vk::ApplicationInfo& applicationInfo = instance.getApplicationInfo();

		ASSERT_NE(applicationInfo, vk::ApplicationInfo());
	}

	TEST_F(InstanceTests, InstanceCreateInfoTest)
	{
		instance.createInstanceCreateInfo();
		const vk::InstanceCreateInfo& instanceCreateInfo = instance.getInstanceCreateInfo();

		ASSERT_NE(instanceCreateInfo, vk::InstanceCreateInfo());
	}

	TEST_F(InstanceTests, CreateInstanceTest)
	{
		Context context;
		instance.create(context);
		const vk::raii::Instance& internalInstance = instance.getInternal();

		ASSERT_NE(*internalInstance, vk::Instance());
	}

	TEST_F(InstanceTests, GetValidationLayersTest)
	{
		const std::vector<const char*>& ValidationLayers = Instance::GetValidationLayers();

		ASSERT_FALSE(ValidationLayers.empty());
	}

	TEST_F(InstanceTests, CheckValidationLayersSupportTest)
	{
		bool result = Instance::CheckValidationLayerSupport();

		ASSERT_TRUE(result);
	}

	TEST_F(InstanceTests, GetRequiredExtensionsTest)
	{
		std::vector<const char*> requiredExtensions = instance.getRequiredExtensions();

		ASSERT_FALSE(requiredExtensions.empty());
	}

	TEST_F(InstanceTests, GetEnableValidationLayersTest)
	{
		bool EnabledValidationLayers = Instance::GetEnabledValidationLayers();
	}

}