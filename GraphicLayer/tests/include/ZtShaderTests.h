#pragma once

#include "Zinet/Renderer/ZtShader.h"
#include "Zinet/Renderer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtShaderTests : public ::testing::Test
{
protected:

	ZtShaderTests()
	{
		Window.InitGLFW();
		Window.CreateWindow();
		Window.InitGLAD();
	}

	ZtWindow Window; // We need to initialize OpenGL context before creating any shader

	ZtShader Shader{};

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
	ZtShaderType ExpectedShaderType = ZtShaderType::Fragment;
	Shader.Create(ExpectedShaderType);

	ZtShaderType ActualShaderType = Shader.GetType();
	ASSERT_EQ(ActualShaderType, ExpectedShaderType);
}

TEST_F(ZtShaderTests, GetIDTest)
{
	GLuint ShaderID = Shader.GetID();
}

TEST_F(ZtShaderTests, CompileTest)
{
	Shader.Create(ZtShaderType::Vertex);
	Shader.LoadFromCString(CStringVertexShaderSource);
	Shader.Compile();

	GLuint ShaderID = Shader.GetID();

	int Success;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Success);

	ASSERT_TRUE(Success);
}

TEST_F(ZtShaderTests, CompileStatusTest)
{
	Shader.Create(ZtShaderType::Vertex);
	Shader.LoadFromCString(CStringVertexShaderSource);
	Shader.Compile();

	bool Status = Shader.CompileStatus();
	ASSERT_TRUE(Status);
}

TEST_F(ZtShaderTests, CompileErrorMessageTest)
{
	Shader.Create(ZtShaderType::Vertex);
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
	Shader.Create(ZtShaderType::Vertex);
	Shader.LoadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.vert");
	Shader.Compile();

	GLuint ShaderID = Shader.GetID();

	int Success = false;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Success);

	if(!Success)
	{ 
		std::string CompileErrorMessage = Shader.CompileErrorMessage();
		std::cout << CompileErrorMessage << '\n';
	}

	ASSERT_TRUE(Success);
}

TEST_F(ZtShaderTests, DeleteTest)
{
	Shader.Create(ZtShaderType::Vertex);
	Shader.Delete();
	GLuint ActualID = Shader.GetID();

	GLboolean IsShader = glIsShader(ActualID);
	ASSERT_FALSE(IsShader);

	GLuint ExpectedID = ZtShader::InvalidID;
	ASSERT_EQ(ActualID, ExpectedID);
}