#pragma once

#include "Zinet/GraphicLayer/ZtShaderType.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtShaderTypeTests : public ::testing::Test
	{
	protected:

		ShaderType shaderType{};

	};

	TEST_F(ZtShaderTypeTests, PassTest)
	{
	}

}