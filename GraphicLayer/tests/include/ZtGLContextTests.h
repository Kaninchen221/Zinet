#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ContextTests : public ::testing::Test
	{
	protected:

		Context context;

	};

	TEST_F(ContextTests, GetInternal)
	{
		[[maybe_unused]] vk::raii::Context& internal = context.getInternal();
	}

	TEST_F(ContextTests, ArrowOperator)
	{
		vk::raii::Context* internal = context.operator->();

		ASSERT_NE(internal, nullptr);
	}
}