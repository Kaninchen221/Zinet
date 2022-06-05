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

	TEST_F(InstanceTests, EnumeratePhysicalDevices)
	{
		Context context;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.getRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
		vk::raii::PhysicalDevices physicalDevices = instance.enumeratePhysicalDevices();
	}

	TEST_F(InstanceTests, ApplicationInfoTest)
	{
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		vk::ApplicationInfo notExpected{};

		ASSERT_NE(applicationInfo, notExpected);
	}

	TEST_F(InstanceTests, InstanceCreateInfoTest)
	{
		vk::ApplicationInfo&& applicationInfo = instance.createApplicationInfo();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);

		ASSERT_NE(instanceCreateInfo, vk::InstanceCreateInfo());
	}

	TEST_F(InstanceTests, CreateInstanceTest)
	{
		Context context;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
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
		std::vector<const char*>& requiredExtensions = instance.getRequiredExtensions();

		ASSERT_FALSE(requiredExtensions.empty());
	}

	TEST_F(InstanceTests, GetEnableValidationLayersTest)
	{
		bool EnabledValidationLayers = Instance::GetEnabledValidationLayers();
	}

}