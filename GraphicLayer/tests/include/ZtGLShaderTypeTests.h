#pragma once

#include "Zinet/GraphicLayer/ZtGLShaderType.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ShaderTypeTests : public ::testing::Test
	{
	protected:

		ShaderType shaderType = ShaderType::Vertex;

	};

	TEST_F(ShaderTypeTests, ShaderTypeToShaderCTest)
	{
		shaderc_shader_kind asShaderc = ShaderTypeToShaderc(shaderType);

		ASSERT_EQ(asShaderc, shaderc_glsl_vertex_shader);
	}

	TEST_F(ShaderTypeTests, ShaderTypeToVkShaderStageTest)
	{
		vk::ShaderStageFlagBits asVkShaderStage = ShaderTypeToVkShaderStage(shaderType);

		ASSERT_EQ(asVkShaderStage, vk::ShaderStageFlagBits::eVertex);
	}
}