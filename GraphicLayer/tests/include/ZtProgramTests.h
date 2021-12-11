#pragma once

#include "Zinet/GraphicLayer/ZtProgram.h"
#include "Zinet/GraphicLayer/ZtWindow.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtVertexArray.h"
#include "Zinet/GraphicLayer/ZtVertexBuffer.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtProgramTests : public ::testing::Test
	{
	protected:

		ZtProgramTests()
		{
			Window.CreateWindow();
		}

		void MakeProgramLinkable(const Program& Program)
		{
			Shader VertexShader;
			VertexShader.Create(ShaderType::Vertex);
			VertexShader.LoadFromCString(VertexShaderSource);
			Program.AttachShader(VertexShader);

			Shader FragmentShader;
			FragmentShader.Create(ShaderType::Fragment);
			FragmentShader.LoadFromCString(FragmentShaderSource);
			Program.AttachShader(FragmentShader);
		}

		Window Window;
		Program Program;

		const char* VertexShaderSource =
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
	}

	TEST_F(ZtProgramTests, AttachShaderTest)
	{
		Shader Shader;
		Shader.Create(ShaderType::Vertex);

		Program.Create();
		Program.AttachShader(Shader);
	}

	TEST_F(ZtProgramTests, LinkProgramTest)
	{
		Program.Create();
		MakeProgramLinkable(Program);

		Program.Link();

		bool LinkStatus = Program.LinkStatus();
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
		GLuint ExpectedID = Program::InvalidID;

		ASSERT_EQ(ActualID, ExpectedID);
	}

	TEST_F(ZtProgramTests, GetUniformTest)
	{
		Program.Create();
		MakeProgramLinkable(Program);
		Program.Link();

		std::string Name = "Uniform1f";
		GLint Uniform = Program.GetUniform(Name);
	}

	TEST_F(ZtProgramTests, SetUniform1fTest)
	{
		Program.Create();
		MakeProgramLinkable(Program);
		Program.Link();
		Program.Use();

		std::string UiformName = "Uniform1";
		Program.SetUniform1f(UiformName, 0.f);
	}

	TEST_F(ZtProgramTests, SetUniform2fTest)
	{
		Program.Create();
		MakeProgramLinkable(Program);
		Program.Link();
		Program.Use();

		std::string Name = "Uniform2";
		glm::vec2 Value;
		Program.SetUniform2f(Name, Value);
	}

	TEST_F(ZtProgramTests, SetUniform3fTest)
	{
		Program.Create();
		MakeProgramLinkable(Program);
		Program.Link();
		Program.Use();

		std::string Name = "Uniform3";
		glm::vec3 Value;
		Program.SetUniform3f(Name, Value);
	}

	TEST_F(ZtProgramTests, SetUniform4fTest)
	{
		Program.Create();
		MakeProgramLinkable(Program);
		Program.Link();
		Program.Use();

		std::string Name = "Uniform4";
		glm::vec4 Value;
		Program.SetUniform4f(Name, Value);
	}

	TEST_F(ZtProgramTests, SetUniformMatrix4fTest)
	{
		Program.Create();
		MakeProgramLinkable(Program);
		Program.Link();
		Program.Use();

		std::string Name = "Uniform5";
		glm::mat4 Value;
		Program.SetUniformMatrix4f(Name, Value);
	}

	TEST_F(ZtProgramTests, PrepareAttributesTest)
	{
		std::vector<Vertex> Vertices{
		   {{ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f}}
		};

		VertexArray VAO;
		VAO.Generate();
		VAO.Bind();

		VertexBuffer VBO;
		VBO.Generate();
		VBO.Bind();
		VBO.SetData(Vertices, BufferUsage::Static);

		Program.Create();
		MakeProgramLinkable(Program);
		Program.PrepareAttributes();
	}

}