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
		Window.CreateWindow();
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
}

TEST_F(ZtElementBufferTests, GetIDTest)
{
	VBO.Generate();
	GLuint ActualID = VBO.GetID();
	GLuint NotExpectedID = ZtElementBuffer::InvalidID;
}

TEST_F(ZtElementBufferTests, BindTest)
{
	VBO.Generate();
	VBO.Bind();
	GLuint ExpectedBindedID = VBO.GetID();
}

TEST_F(ZtElementBufferTests, UnbindTest)
{
	VBO.Generate();
	VBO.Bind();
	VBO.Unbind();
	GLuint NotExpectedBindedID = VBO.GetID();
}

TEST_F(ZtElementBufferTests, SetDataTest)
{
	VBO.Generate();
	VBO.Bind();
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