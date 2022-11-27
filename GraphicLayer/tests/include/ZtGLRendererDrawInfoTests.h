#pragma once

#include "Zinet/GraphicLayer/ZtGLRendererDrawInfo.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class RendererDrawInfoTests : public ::testing::Test
	{
	protected:

		RendererDrawInfo drawInfo;

	};

	TEST_F(RendererDrawInfoTests, Properties)
	{
		static_assert(std::is_same_v<decltype(drawInfo.shaders), std::span<Shader>>);
	}
}
