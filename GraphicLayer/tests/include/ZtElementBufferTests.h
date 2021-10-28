#pragma once

#include "Zinet/GraphicLayer/ZtElementBuffer.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtElementBufferTests : public ::testing::Test
{
protected:

	ZtElementBufferTests()
	{
		Window.InitGLFW();
		Window.CreateWindow();
		Window.InitGLAD();
	}

	~ZtElementBufferTests()
	{
		VBO.Delete();
	}

	ZtElementBuffer VBO;

	ZtWindow Window;

};

TEST_F(ZtElementBufferTests, GenerateTest)
{
	VBO.Generate();
	GLuint ActualID = VBO.GetID();

	GLboolean IsBuffer = glIsBuffer(ActualID);
	ASSERT_TRUE(ActualID);
}

TEST_F(ZtElementBufferTests, GetIDTest)
{
	VBO.Generate();
	GLuint ActualID = VBO.GetID();
	GLuint NotExpectedID = ZtElementBuffer::InvalidID;

	ASSERT_NE(ActualID, NotExpectedID);
}

TEST_F(ZtElementBufferTests, BindTest)
{
	VBO.Generate();
	VBO.Bind();
	GLuint ExpectedBindedID = VBO.GetID();

	GLint ActualBindedID = 0u;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &ActualBindedID);

	ASSERT_EQ(ActualBindedID, ExpectedBindedID);
}

TEST_F(ZtElementBufferTests, UnbindTest)
{
	VBO.Generate();
	VBO.Bind();
	VBO.Unbind();
	GLuint NotExpectedBindedID = VBO.GetID();

	GLint ActualBindedID = 0u;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &ActualBindedID);

	ASSERT_NE(ActualBindedID, NotExpectedBindedID);
}

TEST_F(ZtElementBufferTests, SetDataTest)
{
	VBO.Generate();
	std::array<ZtVertex, 1> Vertices;
	VBO.SetData<std::array<ZtVertex, 1>>(Vertices, ZtBufferUsage::Static);
}

TEST_F(ZtElementBufferTests, InvalidIDTest)
{
	GLuint ActualInvalidID = ZtElementBuffer::InvalidID;
	GLuint ExpectedInvalidID = 0u;

	ASSERT_EQ(ActualInvalidID, ExpectedInvalidID);
}

TEST_F(ZtElementBufferTests, DeleteTest)
{
	VBO.Generate();
	VBO.Delete();

	GLuint ActualID = VBO.GetID();
	GLuint ExpectedID = ZtElementBuffer::InvalidID;

	ASSERT_EQ(ActualID, ExpectedID);
}