#pragma once

#include "Zinet/GraphicLayer/ZtShaderType.h"

#include "gtest/gtest.h"

class ZtShaderTypeTests : public ::testing::Test
{
protected:

	ZtShaderType ShaderType{};

};

TEST_F(ZtShaderTypeTests, EqualToOpenGLTypeTest)
{
	ShaderType = ZtShaderType::Vertex;
	GLuint ShaderTypeAsGLuint = static_cast<GLuint>(ShaderType);

	ASSERT_EQ(ShaderTypeAsGLuint, GL_VERTEX_SHADER);
}