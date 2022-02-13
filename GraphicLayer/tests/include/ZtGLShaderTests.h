#pragma once

#include "Zinet/GraphicLayer/ZtGLShader.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ShaderTests : public ::testing::Test
	{
	protected:

		Shader shader;

		const char* cStringVertexShaderSource =
			"#version 330 core \n"
			"layout(location = 0) in vec3 aPos; \n"
			" \n"
			"void main() \n"
			"{ \n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
			"} \n\0";

		const char* invalidCStringVertexShaderSource =
			"#version 330 core \n"
			"layout(location = 0) in vec3 aPos; \n"
			" \n"
			"void main( \n"
			"{ \n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
			"} \n\0";
	};

	TEST_F(ShaderTests, GetSourceTest)
	{
		std::string_view source = shader.getSource();

		ASSERT_TRUE(source.empty());
	}

	TEST_F(ShaderTests, LoadFromCStringTest)
	{
		shader.loadFromCString(cStringVertexShaderSource);
		std::string_view source = shader.getSource();

		ASSERT_FALSE(source.empty());
	}

	TEST_F(ShaderTests, LoadFromFileTest)
	{
		shader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.vert");
		std::string_view source = shader.getSource();

		ASSERT_FALSE(source.empty());
	}

	TEST_F(ShaderTests, ParseTest)
	{
		shader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.vert");
		bool parseResult = shader.parse();
		
		ASSERT_TRUE(parseResult);
	}
}