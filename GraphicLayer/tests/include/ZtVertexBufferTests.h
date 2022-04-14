#pragma once

#include "Zinet/GraphicLayer/ZtVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtVertexBufferTests : public ::testing::Test
	{
	protected:

		ZtVertexBufferTests()
		{
			window.create();
		}

		VertexBuffer vbo;

		Window window;

	};

	TEST_F(ZtVertexBufferTests, GenerateTest)
	{
		vbo.generate();
		GLuint actualID = vbo.getID();
	}

	TEST_F(ZtVertexBufferTests, GetIDTest)
	{
		vbo.generate();
		GLuint actualID = vbo.getID();
		GLuint notExpectedID = VertexBuffer::InvalidID;
	}

	TEST_F(ZtVertexBufferTests, BindTest)
	{
		vbo.generate();
		vbo.bind();
		GLuint expectedBindedID = vbo.getID();
	}

	TEST_F(ZtVertexBufferTests, UnbindTest)
	{
		vbo.generate();
		vbo.bind();
		vbo.unbind();
		GLuint notExpectedBindedID = vbo.getID();
	}

	TEST_F(ZtVertexBufferTests, SetDataTest)
	{
		vbo.generate();
		vbo.bind();
		std::array<Vertex, 1> vertices;
		vbo.setData<std::array<Vertex, 1>>(vertices, BufferUsage::Static);
	}

	TEST_F(ZtVertexBufferTests, InvalidIDTest)
	{
		GLuint actualInvalidID = VertexBuffer::InvalidID;
		GLuint expectedInvalidID = 0u;

		ASSERT_EQ(actualInvalidID, expectedInvalidID);
	}

	TEST_F(ZtVertexBufferTests, DeleteTest)
	{
		vbo.generate();
		vbo.deleteResource();

		GLuint actualID = vbo.getID();
		GLuint expectedID = VertexBuffer::InvalidID;

		ASSERT_EQ(actualID, expectedID);
	}

}