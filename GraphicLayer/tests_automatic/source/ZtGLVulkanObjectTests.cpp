#pragma once

#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class VulkanObjectTests : public ::testing::Test
	{
	protected:

		class TestClass : public VulkanObject<vk::raii::Instance>
		{

		};

		TestClass testObject;

	};

	TEST_F(VulkanObjectTests, GetInternal)
	{
		vk::raii::Instance& internal = testObject.getInternal();

		ASSERT_EQ(*internal, *vk::raii::Instance{ std::nullptr_t{} });
	}

	TEST_F(VulkanObjectTests, GetInternalConst)
	{
		[](const TestClass& constReference) 
		{
			const vk::raii::Instance& internal = constReference.getInternal();
			ASSERT_EQ(*internal, *vk::raii::Instance{ std::nullptr_t{} });
		}
		(testObject);
	}

	TEST_F(VulkanObjectTests, ArrowOperator)
	{
		vk::raii::Instance* internal = testObject.operator->();

		ASSERT_NE(internal, nullptr);
	}

	TEST_F(VulkanObjectTests, ArrowOperatorConst)
	{
		[](const TestClass& constReference)
		{
			const vk::raii::Instance* internal = constReference.operator->();
			ASSERT_NE(internal, nullptr);
		}
		(testObject);
	}

	TEST_F(VulkanObjectTests, ComparisonEqualToInternalType)
	{
		ASSERT_EQ(testObject, vk::raii::Instance(std::nullptr_t{}));
	}

	TEST_F(VulkanObjectTests, ComparisonNotEqualToInternalType)
	{
		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		ASSERT_NE(testObject, instance.getInternal());
	}

	TEST_F(VulkanObjectTests, ComparisonEqualToOther)
	{
		TestClass testObject2;
		ASSERT_EQ(testObject, testObject2);
	}

	TEST_F(VulkanObjectTests, getVk)
	{
		vk::Instance vkInstance = testObject.getVk();
	}

	TEST(VulkanObject, IsValid)
	{
		Instance instance;
		bool isValid = instance.isValid();
		ASSERT_FALSE(isValid);

		Context context;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		isValid = instance.isValid();
		ASSERT_TRUE(isValid);
	}
}
