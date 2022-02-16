#pragma once

#include "Zinet/GraphicLayer/ZtVertexArray.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtVertexArrayTests : public ::testing::Test
	{
	protected:

		ZtVertexArrayTests()
		{
			window.createWindow();
		}

		~ZtVertexArrayTests()
		{
			vao.deleteResource();
		}

		VertexArray vao;
		Window window;

	};

	TEST_F(ZtVertexArrayTests, generateTest)
	{
		vao.generate();
		GLuint actualID = vao.getID();
		GLuint expectedID = 1u;
	}

	TEST_F(ZtVertexArrayTests, getIDTest)
	{
		GLuint actualID = vao.getID();
		GLuint expectedID = VertexArray::InvalidID;

		ASSERT_EQ(actualID, expectedID);
	}

	TEST_F(ZtVertexArrayTests, bindTest)
	{
		vao.generate();
		vao.bind();
		GLuint iD = vao.getID();
	}

	TEST_F(ZtVertexArrayTests, UnbindTest)
	{
		vao.generate();
		vao.bind();
		vao.unbind();

		GLint actualBindedVertexArray = VertexArray::InvalidID;
	}

	TEST_F(ZtVertexArrayTests, DeleteTest)
	{
		vao.generate();
		GLuint previouseiD = vao.getID();
		vao.deleteResource();

		GLuint actualID = vao.getID();
		GLuint expectedID = VertexArray::InvalidID;
		ASSERT_EQ(actualID, expectedID);
	}

}