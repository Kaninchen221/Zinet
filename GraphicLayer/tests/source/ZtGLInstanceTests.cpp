#pragma once

#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class InstanceTests : public ::testing::Test
	{
	protected:

		Instance instance{};

		static_assert(std::derived_from<Instance, VulkanObject<vk::raii::Instance>>);
	};

	TEST_F(InstanceTests, EnumeratePhysicalDevices)
	{
		Context context;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
		vk::raii::PhysicalDevices physicalDevices = instance.enumeratePhysicalDevices();
	}

	TEST_F(InstanceTests, ApplicationInfo)
	{
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		vk::ApplicationInfo notExpected{};

		ASSERT_NE(applicationInfo, notExpected);
	}

	TEST_F(InstanceTests, InstanceCreateInfo)
	{
		vk::ApplicationInfo&& applicationInfo = instance.createApplicationInfo();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);

		ASSERT_NE(instanceCreateInfo, vk::InstanceCreateInfo());
	}

	TEST_F(InstanceTests, CreateInstance)
	{
		Context context;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);
		const vk::raii::Instance& internalInstance = instance.getInternal();

		ASSERT_NE(*internalInstance, vk::Instance());
	}

	TEST_F(InstanceTests, GetValidationLayers)
	{
		const std::vector<const char*>& ValidationLayers = Instance::GetValidationLayers();

		ASSERT_FALSE(ValidationLayers.empty());
	}

	TEST_F(InstanceTests, CheckValidationLayersSupport)
	{
		bool result = Instance::CheckValidationLayerSupport();

		ASSERT_TRUE(result);
	}

	TEST_F(InstanceTests, GetRequiredExtensions)
	{
		std::vector<const char*>& requiredExtensions = instance.getRequiredExtensions();

		ASSERT_TRUE(requiredExtensions.empty());
	}

	TEST_F(InstanceTests, PopulateRequiredExtensions)
	{
		instance.populateRequiredExtensions();
		std::vector<const char*>& requiredExtensions = instance.getRequiredExtensions();
		ASSERT_FALSE(requiredExtensions.empty());
	}

	TEST_F(InstanceTests, GetEnableValidationLayers)
	{
		[[maybe_unused]] bool EnabledValidationLayers = Instance::GetEnabledValidationLayers();
	}

}