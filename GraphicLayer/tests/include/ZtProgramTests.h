#pragma once

#include "Zinet/GraphicLayer/ZtProgram.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtProgramTests : public ::testing::Test
{
protected:

	ZtProgramTests()
	{
		Window.CreateWindow();
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
	ZtProgram Program;

	const char* VertexShaderSource =
		"#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		" \n"
		"uniform float Uniform1; \n"
		"uniform vec2 Uniform2; \n"
		"uniform vec3 Uniform3; \n"
		"uniform vec4 Uniform4; \n"
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
	Program.Create();
}

TEST_F(ZtProgramTests, GetIDTest)
{
	Program.Create();
	GLuint ActualID = Program.GetID();
	GLuint ExpectedID = 1u;
	ASSERT_EQ(ActualID, ExpectedID);
}

TEST_F(ZtProgramTests, AttachShaderTest)
{
	ZtShader Shader;
	Shader.Create(ZtShaderType::Vertex);

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
	Program.Create();
	MakeProgramLinkable(Program);

	Program.Link();

	bool LinkStatus = Program.LinkStatus();
	ASSERT_TRUE(LinkStatus);
}

TEST_F(ZtProgramTests, LinkStatusTest)
{
	Program.Create();
	bool LinkStatus = Program.LinkStatus();
	ASSERT_FALSE(LinkStatus);
}

TEST_F(ZtProgramTests, IsValidTest)
{
	Program.Create();
	bool IsValid = Program.IsValid();
	ASSERT_FALSE(IsValid);
}

TEST_F(ZtProgramTests, InfoLogTest)
{
	Program.Create();
	std::string InfoLog = Program.InfoLog();

	ASSERT_EQ(InfoLog.size(), 0);
}

TEST_F(ZtProgramTests, UseProgramTest)
{
	Program.Create();
	MakeProgramLinkable(Program);

	Program.Link();
	Program.Use();
}

TEST_F(ZtProgramTests, DeleteTest)
{
	Program.Create();
	Program.Delete();

	GLuint ActualID = Program.GetID();
	GLuint ExpectedID = ZtProgram::InvalidID;

	ASSERT_EQ(ActualID, ExpectedID);
}

TEST_F(ZtProgramTests, GetUniformTest)
{
	Program.Create();
	MakeProgramLinkable(Program);
	Program.Link();

	std::string Name = "Uniform1f";
	GLint Uniform = Program.GetUniform(Name);

	ASSERT_NE(Uniform, 0);
}

TEST_F(ZtProgramTests, SetUniform1fTest)
{
	Program.Create();
	MakeProgramLinkable(Program);
	Program.Link();

	std::string Name = "Uniform1";
	GLint Uniform = Program.GetUniform(Name);

	Program.Use();
	Program.SetUniform1f(Uniform, 0.f);
}

TEST_F(ZtProgramTests, SetUniform2fTest)
{
	Program.Create();
	MakeProgramLinkable(Program);
	Program.Link();

	std::string Name = "Uniform2";
	GLint Uniform = Program.GetUniform(Name);

	Program.Use();
	glm::vec2 Value;
	Program.SetUniform2f(Uniform, Value);
}

TEST_F(ZtProgramTests, SetUniform3fTest)
{
	Program.Create();
	MakeProgramLinkable(Program);
	Program.Link();

	std::string Name = "Uniform3";
	GLint Uniform = Program.GetUniform(Name);

	Program.Use();
	glm::vec3 Value;
	Program.SetUniform3f(Uniform, Value);
}

TEST_F(ZtProgramTests, SetUniform4fTest)
{
	Program.Create();
	MakeProgramLinkable(Program);
	Program.Link();

	std::string Name = "Uniform4";
	GLint Uniform = Program.GetUniform(Name);

	Program.Use();
	glm::vec4 Value;
	Program.SetUniform4f(Uniform, Value);
}