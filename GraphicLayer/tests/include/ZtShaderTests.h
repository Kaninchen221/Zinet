#pragma once

#include "Zinet/GraphicLayer/ZtShader.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtShaderTests : public ::testing::Test
	{
	protected:

		ZtShaderTests()
		{
			window.createWindow();
		}

		Window window; // We need to initialize OpenGL context before creating any shader

		Shader shader{};

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

	TEST_F(ZtShaderTests, CreateTest)
	{
		ShaderType expectedShaderType = ShaderType::Fragment;
		shader.create(expectedShaderType);

		ShaderType actualShaderType = shader.getType();
		ASSERT_EQ(actualShaderType, expectedShaderType);
	}

	TEST_F(ZtShaderTests, GetIDTest)
	{
		GLuint shaderID = shader.getID();
	}

	TEST_F(ZtShaderTests, CompileTest)
	{
		shader.create(ShaderType::Vertex);
		shader.loadFromCString(cStringVertexShaderSource);
		shader.compile();

		unsigned int shaderID = shader.getID();
	}

	TEST_F(ZtShaderTests, CompileStatusTest)
	{
		shader.create(ShaderType::Vertex);
		shader.loadFromCString(cStringVertexShaderSource);
		shader.compile();

		bool status = shader.compileStatus();
	}

	TEST_F(ZtShaderTests, CompileErrorMessageTest)
	{
		shader.create(ShaderType::Vertex);
		shader.loadFromCString(invalidCStringVertexShaderSource);
		shader.compile();
		bool status = shader.compileStatus();
		ASSERT_FALSE(status);

		std::string message = shader.compileErrorMessage();
		size_t messageSize = message.size();
		ASSERT_GT(messageSize, 0);
	}

	TEST_F(ZtShaderTests, LoadFromFileTest)
	{
		shader.create(ShaderType::Vertex);
		shader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.vert");
		shader.compile();

		GLuint shaderID = shader.getID();
	}

	TEST_F(ZtShaderTests, DeleteTest)
	{
		shader.create(ShaderType::Vertex);
		shader.deleteResource();
		GLuint actualID = shader.getID();

		GLuint expectedID = Shader::InvalidID;
		ASSERT_EQ(actualID, expectedID);
	}

}