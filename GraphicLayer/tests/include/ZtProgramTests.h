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
			window.createWindow();
		}

		void makeProgramLinkable(const Program& program)
		{
			Shader vertexShader;
			vertexShader.create(ShaderType::Vertex);
			vertexShader.loadFromCString(vertexShaderSource);
			program.attachShader(vertexShader);

			Shader fragmentShader;
			fragmentShader.create(ShaderType::Fragment);
			fragmentShader.loadFromCString(fragmentShaderSource);
			program.attachShader(fragmentShader);
		}

		Window window;
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

	TEST_F(ZtProgramTests, CreateTest)
	{
		program.create();
	}

	TEST_F(ZtProgramTests, GetIDTest)
	{
		program.create();
		GLuint actualID = program.getID();
		GLuint expectedID = 1u;
	}

	TEST_F(ZtProgramTests, AttachShaderTest)
	{
		Shader shader;
		shader.create(ShaderType::Vertex);

		program.create();
		program.attachShader(shader);
	}

	TEST_F(ZtProgramTests, LinkProgramTest)
	{
		program.create();
		makeProgramLinkable(program);

		program.link();

		bool linkStatus = program.linkStatus();
	}

	TEST_F(ZtProgramTests, LinkStatusTest)
	{
		program.create();
		bool linkStatus = program.linkStatus();
		ASSERT_FALSE(linkStatus);
	}

	TEST_F(ZtProgramTests, IsValidTest)
	{
		program.create();
		bool isValid = program.isValid();
		ASSERT_FALSE(isValid);
	}

	TEST_F(ZtProgramTests, InfoLogTest)
	{
		program.create();
		std::string infoLog = program.infoLog();

		ASSERT_EQ(infoLog.size(), 0);
	}

	TEST_F(ZtProgramTests, UseProgramTest)
	{
		program.create();
		makeProgramLinkable(program);

		program.link();
		program.use();
	}

	TEST_F(ZtProgramTests, DeleteTest)
	{
		program.create();
		program.deleteResource();

		GLuint actualID = program.getID();
		GLuint expectedID = Program::InvalidID;

		ASSERT_EQ(actualID, expectedID);
	}

	TEST_F(ZtProgramTests, GetUniformTest)
	{
		program.create();
		makeProgramLinkable(program);
		program.link();

		std::string name = "Uniform1f";
		GLint uniform = program.getUniform(name);
	}

	TEST_F(ZtProgramTests, SetUniform1fTest)
	{
		program.create();
		makeProgramLinkable(program);
		program.link();
		program.use();

		std::string uniformName = "Uniform1";
		program.setUniform1f(uniformName, 0.f);
	}

	TEST_F(ZtProgramTests, SetUniform2fTest)
	{
		program.create();
		makeProgramLinkable(program);
		program.link();
		program.use();

		std::string name = "Uniform2";
		glm::vec2 value;
		program.setUniform2f(name, value);
	}

	TEST_F(ZtProgramTests, SetUniform3fTest)
	{
		program.create();
		makeProgramLinkable(program);
		program.link();
		program.use();

		std::string name = "Uniform3";
		glm::vec3 value;
		program.setUniform3f(name, value);
	}

	TEST_F(ZtProgramTests, SetUniform4fTest)
	{
		program.create();
		makeProgramLinkable(program);
		program.link();
		program.use();

		std::string name = "Uniform4";
		glm::vec4 value;
		program.setUniform4f(name, value);
	}

	TEST_F(ZtProgramTests, SetUniformMatrix4fTest)
	{
		program.create();
		makeProgramLinkable(program);
		program.link();
		program.use();

		std::string name = "Uniform5";
		glm::mat4 value;
		program.setUniformMatrix4f(name, value);
	}

	TEST_F(ZtProgramTests, PrepareAttributesTest)
	{
		std::vector<Vertex> vertices{
		   {{ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f}}
		};

		VertexArray vao;
		vao.generate();
		vao.bind();

		VertexBuffer vbo;
		vbo.generate();
		vbo.bind();
		vbo.setData(vertices, BufferUsage::Static);

		program.create();
		makeProgramLinkable(program);
		program.prepareAttributes();
	}

}