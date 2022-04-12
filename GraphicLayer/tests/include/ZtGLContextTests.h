#pragma once

#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ContextTests : public ::testing::Test
	{
	protected:

		Context context;

	};

	TEST_F(ContextTests, GetInternalTest)
	{
		vk::raii::Context& internal = context.getInternal();
	}

}