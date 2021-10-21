#pragma once

#include "Zinet/Renderer/ZtProgram.h"
#include "Zinet/Renderer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtProgramTests : public ::testing::Test
{
protected:

	ZtProgramTests()
	{
		Window.InitGLFW();
		Window.CreateWindow();
		Window.InitGLAD();
		Window.InitOpenGL();
	}

	void MakeProgramLinkable(const ZtProgram& Program)
	{
		ZtShader VertexShader;
		VertexShader.Create(ZtShaderType::Vertex);
		VertexShader.LoadFromCString(VertexShaderSource);
		Program.AttachShader(VertexShader);

		ZtShader FragmentShader;
		FragmentShader.Create(ZtShaderType::Fragment);
		FragmentShader.LoadFromCString(FragmentShaderSource);
		Program.AttachShader(FragmentShader);
	}

	ZtWindow Window;

	const char* VertexShaderSource =
		"#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		" \n"
		"void main() \n"
		"{ \n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
		"} \n\0";

	const char* FragmentShaderSource =
		"#version 330 core \n"
		"out vec4 FragColor; \n"
		" \n"
		"void main() \n"
		"{ \n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
		"} \n\0";

};

TEST_F(ZtProgramTests, CreateTest)
{
	ZtProgram Program;
	Program.Create();
}

TEST_F(ZtProgramTests, GetIDTest)
{
	ZtProgram Program;
	Program.Create();
	GLuint ActualID = Program.GetID();
	GLuint ExpectedID = 1u;
	ASSERT_EQ(ActualID, ExpectedID);
}

TEST_F(ZtProgramTests, AttachShaderTest)
{
	ZtShader Shader;
	Shader.Create(ZtShaderType::Vertex);
	ZtProgram Program;
	Program.Create();
	Program.AttachShader(Shader);
	
	constexpr GLsizei MaxShadersCount = 1;
	GLsizei ActualAttachedShadersCount = 0;
	GLuint ActualAttachedShaders[MaxShadersCount];
	glGetAttachedShaders(Program.GetID(), MaxShadersCount, &ActualAttachedShadersCount, ActualAttachedShaders);

	GLsizei ExpectedAttachedShadersCount = 1;
	ASSERT_EQ(ExpectedAttachedShadersCount, ActualAttachedShadersCount);
}

TEST_F(ZtProgramTests, LinkProgramTest)
{
	ZtProgram Program;
	Program.Create();
	MakeProgramLinkable(Program);

	Program.LinkProgram();

	bool LinkStatus = Program.LinkStatus();
	ASSERT_TRUE(LinkStatus);
}

TEST_F(ZtProgramTests, LinkStatusTest)
{
	ZtProgram Program;
	Program.Create();
	bool LinkStatus = Program.LinkStatus();
	ASSERT_FALSE(LinkStatus);
}

TEST_F(ZtProgramTests, IsValidTest)
{
	ZtProgram Program;
	Program.Create();
	bool IsValid = Program.IsValid();
	ASSERT_FALSE(IsValid);
}

TEST_F(ZtProgramTests, InfoLogTest)
{
	ZtProgram Program;
	Program.Create();
	std::string InfoLog = Program.InfoLog();

	ASSERT_EQ(InfoLog.size(), 0);
}

TEST_F(ZtProgramTests, UseProgramTest)
{
	ZtProgram Program;
	Program.Create();
	MakeProgramLinkable(Program);

	Program.LinkProgram();
	Program.UseProgram();
}