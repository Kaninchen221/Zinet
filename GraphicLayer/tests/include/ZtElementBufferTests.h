#pragma once

#include "Zinet/GraphicLayer/ZtElementBuffer.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtElementBufferTests : public ::testing::Test
	{
	protected:

		ZtElementBufferTests()
		{
			window.create();
		}

		~ZtElementBufferTests()
		{
			vbo.deleteResource();
		}

		ElementBuffer vbo;

		Window window;

	};

	TEST_F(ZtElementBufferTests, GenerateTest)
	{
		vbo.generate();
		GLuint actualID = vbo.getID();
	}

	TEST_F(ZtElementBufferTests, GetIDTest)
	{
		vbo.generate();
		GLuint actualID = vbo.getID();
		GLuint notExpectedID = ElementBuffer::InvalidID;
	}

	TEST_F(ZtElementBufferTests, BindTest)
	{
		vbo.generate();
		vbo.bind();
		GLuint expectedBindedID = vbo.getID();
	}

	TEST_F(ZtElementBufferTests, UnbindTest)
	{
		vbo.generate();
		vbo.bind();
		vbo.unbind();
		GLuint notExpectedBindedID = vbo.getID();
	}

	TEST_F(ZtElementBufferTests, SetDataTest)
	{
		vbo.generate();
		vbo.bind();
		std::array<Vertex, 1> vertices;
		vbo.setData<std::array<Vertex, 1>>(vertices, BufferUsage::Static);
	}

	TEST_F(ZtElementBufferTests, InvalidIDTest)
	{
		GLuint actualInvalidID = ElementBuffer::InvalidID;
		GLuint expectedInvalidID = 0u;

		ASSERT_EQ(actualInvalidID, expectedInvalidID);
	}

	TEST_F(ZtElementBufferTests, DeleteTest)
	{
		vbo.generate();
		vbo.deleteResource();

		GLuint actualID = vbo.getID();
		GLuint expectedID = ElementBuffer::InvalidID;

		ASSERT_EQ(actualID, expectedID);
	}

}