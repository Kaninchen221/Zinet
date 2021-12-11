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
			window.CreateWindow();
		}

		Window window; // We need to initialize OpenGL context before creating any shader

		Shader Shader{};

		const char* CStringVertexShaderSource =
			"#version 330 core \n"
			"layout(location = 0) in vec3 aPos; \n"
			" \n"
			"void main() \n"
			"{ \n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
			"} \n\0";

		const char* InvalidCStringVertexShaderSource =
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
		ShaderType ExpectedShaderType = ShaderType::Fragment;
		Shader.Create(ExpectedShaderType);

		ShaderType ActualShaderType = Shader.GetType();
		ASSERT_EQ(ActualShaderType, ExpectedShaderType);
	}

	TEST_F(ZtShaderTests, GetIDTest)
	{
		GLuint ShaderID = Shader.GetID();
	}

	TEST_F(ZtShaderTests, CompileTest)
	{
		Shader.Create(ShaderType::Vertex);
		Shader.LoadFromCString(CStringVertexShaderSource);
		Shader.Compile();

		unsigned int ShaderID = Shader.GetID();
	}

	TEST_F(ZtShaderTests, CompileStatusTest)
	{
		Shader.Create(ShaderType::Vertex);
		Shader.LoadFromCString(CStringVertexShaderSource);
		Shader.Compile();

		bool Status = Shader.CompileStatus();
	}

	TEST_F(ZtShaderTests, CompileErrorMessageTest)
	{
		Shader.Create(ShaderType::Vertex);
		Shader.LoadFromCString(InvalidCStringVertexShaderSource);
		Shader.Compile();
		bool Status = Shader.CompileStatus();
		ASSERT_FALSE(Status);

		std::string Message = Shader.CompileErrorMessage();
		size_t MessageSize = Message.size();
		ASSERT_GT(MessageSize, 0);
	}

	TEST_F(ZtShaderTests, LoadFromFileTest)
	{
		Shader.Create(ShaderType::Vertex);
		Shader.LoadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.vert");
		Shader.Compile();

		GLuint ShaderID = Shader.GetID();
	}

	TEST_F(ZtShaderTests, DeleteTest)
	{
		Shader.Create(ShaderType::Vertex);
		Shader.Delete();
		GLuint ActualID = Shader.GetID();

		GLuint ExpectedID = Shader::InvalidID;
		ASSERT_EQ(ActualID, ExpectedID);
	}

}