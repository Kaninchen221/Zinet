#pragma once

#include "Zinet/GraphicLayer/ZtVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtVertexBufferTests : public ::testing::Test
{
protected:

	ZtVertexBufferTests()
	{
		Window.CreateWindow();
	}

	ZtVertexBuffer VBO;

	ZtWindow Window;

};

TEST_F(ZtVertexBufferTests, GenerateTest)
{
	VBO.Generate();
	GLuint ActualID = VBO.GetID();

	GLboolean IsBuffer = glIsBuffer(ActualID);
	ASSERT_TRUE(ActualID);
}

TEST_F(ZtVertexBufferTests, GetIDTest)
{
	VBO.Generate();
	GLuint ActualID = VBO.GetID();
	GLuint NotExpectedID = ZtVertexBuffer::InvalidID;

	ASSERT_NE(ActualID, NotExpectedID);
}

TEST_F(ZtVertexBufferTests, BindTest)
{
	VBO.Generate();
	VBO.Bind();
	GLuint ExpectedBindedID = VBO.GetID();

	GLint ActualBindedID = 0u;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &ActualBindedID);

	ASSERT_EQ(ActualBindedID, ExpectedBindedID);
}

TEST_F(ZtVertexBufferTests, UnbindTest)
{
	VBO.Generate();
	VBO.Bind();
	VBO.Unbind();
	GLuint NotExpectedBindedID = VBO.GetID();

	GLint ActualBindedID = 0u;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &ActualBindedID);

	ASSERT_NE(ActualBindedID, NotExpectedBindedID);
}

TEST_F(ZtVertexBufferTests, SetDataTest)
{
	VBO.Generate();
	VBO.Bind();
	std::array<ZtVertex, 1> Vertices;
	VBO.SetData<std::array<ZtVertex, 1>>(Vertices, ZtBufferUsage::Static);
}

TEST_F(ZtVertexBufferTests, InvalidIDTest)
{
	GLuint ActualInvalidID = ZtVertexBuffer::InvalidID;
	GLuint ExpectedInvalidID = 0u;

	ASSERT_EQ(ActualInvalidID, ExpectedInvalidID);
}

TEST_F(ZtVertexBufferTests, DeleteTest)
{
	VBO.Generate();
	VBO.Delete();

	GLuint ActualID = VBO.GetID();
	GLuint ExpectedID = ZtVertexBuffer::InvalidID;

	ASSERT_EQ(ActualID, ExpectedID);
}