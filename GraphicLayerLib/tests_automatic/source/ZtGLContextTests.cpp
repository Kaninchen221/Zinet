#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"

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