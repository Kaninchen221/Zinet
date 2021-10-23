#pragma once

#include "Zinet/Renderer/ZtVertexArray.h"
#include "Zinet/Renderer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtVertexArrayTests : public ::testing::Test
{
protected:

	ZtVertexArrayTests()
	{
		Window.InitGLFW();
		Window.CreateWindow();
		Window.InitGLAD();
	}

	~ZtVertexArrayTests()
	{
		VAO.Delete();
	}

	ZtVertexArray VAO;
	ZtWindow Window;

};

TEST_F(ZtVertexArrayTests, GenerateTest)
{
	VAO.Generate();
	GLuint ActualID = VAO.GetID();
	GLuint ExpectedID = 1u;

	ASSERT_EQ(ActualID, ExpectedID);
}

TEST_F(ZtVertexArrayTests, GetIDTest)
{
	GLuint ActualID = VAO.GetID();
	GLuint ExpectedID = ZtVertexArray::InvalidID;

	ASSERT_EQ(ActualID, ExpectedID);
}

TEST_F(ZtVertexArrayTests, BindTest)
{
	VAO.Generate();
	VAO.Bind();
	GLuint ID = VAO.GetID();
	GLboolean IsVertexArray = glIsVertexArray(ID);

	ASSERT_TRUE(IsVertexArray);
}

TEST_F(ZtVertexArrayTests, UnbindTest)
{
	VAO.Generate();
	VAO.Bind();
	VAO.Unbind();

	GLint ActualBindedVertexArray = ZtVertexArray::InvalidID;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &ActualBindedVertexArray);

	GLint NotExpectedVertexArray = VAO.GetID();
	ASSERT_NE(ActualBindedVertexArray, NotExpectedVertexArray);
}

TEST_F(ZtVertexArrayTests, DeleteTest)
{
	VAO.Generate();
	GLuint PreviouseID = VAO.GetID();
	VAO.Delete();

	GLboolean IsVertexArray = glIsVertexArray(PreviouseID);
	ASSERT_FALSE(IsVertexArray);

	GLuint ActualID = VAO.GetID();
	GLuint ExpectedID = ZtVertexArray::InvalidID;
	ASSERT_EQ(ActualID, ExpectedID);
}