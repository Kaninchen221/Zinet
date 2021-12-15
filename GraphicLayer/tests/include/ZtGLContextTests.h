#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class GLContextTests : public ::testing::Test
	{
	protected:

		Context context;

	};

	TEST_F(GLContextTests, InitGLFWTest)
	{
		bool result = context.initGLFW();

		ASSERT_TRUE(result);
	}

	TEST_F(GLContextTests, DeinitGLFWTest)
	{
		context.initGLFW();
		context.deinitGLFW();
	}

	TEST_F(GLContextTests, ApplicationInfoTest)
	{
		context.initGLFW();
		context.createApplicationInfo();
		const vk::ApplicationInfo& applicationInfo = context.getApplicationInfo();

		ASSERT_NE(applicationInfo, vk::ApplicationInfo());
	}

	TEST_F(GLContextTests, InstanceCreateInfoTest)
	{
		context.initGLFW();
		context.createInstanceCreateInfo();
		const vk::InstanceCreateInfo& instanceCreateInfo = context.getInstanceCreateInfo();

		ASSERT_NE(instanceCreateInfo, vk::InstanceCreateInfo());
	}

	TEST_F(GLContextTests, CreateInstanceTest)
	{
		context.initGLFW();
		context.createInstance();
		const vk::Instance& instance = context.getInstance();

		ASSERT_NE(instance, vk::Instance());
	}
}