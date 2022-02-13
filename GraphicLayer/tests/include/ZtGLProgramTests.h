#pragma once

#include "Zinet/GraphicLayer/ZtGLProgram.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtProgramTests : public ::testing::Test
	{
	protected:

		Program program;

		const char* vertexShaderSource =
			"#version 330 core \n"
			"layout(location = 0) in vec3 aPos; \n"
			" \n"
			"uniform float Uniform1; \n"
			"uniform vec2 Uniform2; \n"
			"uniform vec3 Uniform3; \n"
			"uniform vec4 Uniform4; \n"
			"uniform mat4 Uniform5; \n"
			" \n"
			"void main() \n"
			"{ \n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
			"} \n\0";

		const char* fragmentShaderSource =
			"#version 330 core \n"
			"out vec4 FragColor; \n"
			" \n"
			"void main() \n"
			"{ \n"
			"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
			"} \n\0";

	};

	TEST_F(ZtProgramTests, AttachShaderTest)
	{
		Shader shader;
		program.attachShader(shader);
	}

	TEST_F(ZtProgramTests, LinkTest)
	{
		Shader shader;
		program.attachShader(shader);
		bool linkResult = program.link();

		ASSERT_TRUE(linkResult);
	}

	TEST_F(ZtProgramTests, GetSPVTest)
	{
		Shader shader;
		program.attachShader(shader);
		program.link();
		//std::vector<unsigned int> spv = program.getSPV();

		//ASSERT_FALSE(spv.empty());
	}static_cast(false, "Use shaderc instead of this fucking useless shit glaslang kurwa");

}