#pragma once

#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class InstanceTests : public ::testing::Test
	{
	protected:

		Instance instance{};

	};

	TEST(Instance, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Instance, VulkanObject<vk::raii::Instance>>);
	}

	TEST_F(InstanceTests, ApplicationInfoTest)
	{
		instance.createApplicationInfo();
		vk::ApplicationInfo applicationInfo = instance.getApplicationInfo();
		vk::ApplicationInfo notExpected{};

		ASSERT_NE(applicationInfo, notExpected);
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