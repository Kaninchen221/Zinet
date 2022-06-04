#pragma once

#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "gtest/gtest.h"

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
		[](const TestClass& testObject) 
		{
			const vk::raii::Instance& internal = testObject.getInternal();
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
		[](const TestClass& testObject) 
		{
			const vk::raii::Instance* internal = testObject.operator->();
			ASSERT_NE(internal, nullptr);
		}
		(testObject);
	}
}
