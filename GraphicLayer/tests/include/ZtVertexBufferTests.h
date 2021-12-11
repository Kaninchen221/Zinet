#pragma once

#include "Zinet/GraphicLayer/ZtVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtVertexBufferTests : public ::testing::Test
	{
	protected:

		ZtVertexBufferTests()
		{
			Window.CreateWindow();
		}

		VertexBuffer VBO;

		Window Window;

	};

	TEST_F(ZtVertexBufferTests, GenerateTest)
	{
		VBO.Generate();
		GLuint ActualID = VBO.GetID();
	}

	TEST_F(ZtVertexBufferTests, GetIDTest)
	{
		VBO.Generate();
		GLuint ActualID = VBO.GetID();
		GLuint NotExpectedID = VertexBuffer::InvalidID;
	}

	TEST_F(ZtVertexBufferTests, BindTest)
	{
		VBO.Generate();
		VBO.Bind();
		GLuint ExpectedBindedID = VBO.GetID();
	}

	TEST_F(ZtVertexBufferTests, UnbindTest)
	{
		VBO.Generate();
		VBO.Bind();
		VBO.Unbind();
		GLuint NotExpectedBindedID = VBO.GetID();
	}

	TEST_F(ZtVertexBufferTests, SetDataTest)
	{
		VBO.Generate();
		VBO.Bind();
		std::array<Vertex, 1> Vertices;
		VBO.SetData<std::array<Vertex, 1>>(Vertices, BufferUsage::Static);
	}

	TEST_F(ZtVertexBufferTests, InvalidIDTest)
	{
		GLuint ActualInvalidID = VertexBuffer::InvalidID;
		GLuint ExpectedInvalidID = 0u;

		ASSERT_EQ(ActualInvalidID, ExpectedInvalidID);
	}

	TEST_F(ZtVertexBufferTests, DeleteTest)
	{
		VBO.Generate();
		VBO.Delete();

		GLuint ActualID = VBO.GetID();
		GLuint ExpectedID = VertexBuffer::InvalidID;

		ASSERT_EQ(ActualID, ExpectedID);
	}

}