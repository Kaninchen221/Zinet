#pragma once

#include "Zinet/GraphicLayer/ZtVertexArray.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtVertexArrayTests : public ::testing::Test
	{
	protected:

		ZtVertexArrayTests()
		{
			Window.CreateWindow();
		}

		~ZtVertexArrayTests()
		{
			VAO.Delete();
		}

		VertexArray VAO;
		Window Window;

	};

	TEST_F(ZtVertexArrayTests, GenerateTest)
	{
		VAO.Generate();
		GLuint ActualID = VAO.GetID();
		GLuint ExpectedID = 1u;
	}

	TEST_F(ZtVertexArrayTests, GetIDTest)
	{
		GLuint ActualID = VAO.GetID();
		GLuint ExpectedID = VertexArray::InvalidID;

		ASSERT_EQ(ActualID, ExpectedID);
	}

	TEST_F(ZtVertexArrayTests, BindTest)
	{
		VAO.Generate();
		VAO.Bind();
		GLuint ID = VAO.GetID();
	}

	TEST_F(ZtVertexArrayTests, UnbindTest)
	{
		VAO.Generate();
		VAO.Bind();
		VAO.Unbind();

		GLint ActualBindedVertexArray = VertexArray::InvalidID;
	}

	TEST_F(ZtVertexArrayTests, DeleteTest)
	{
		VAO.Generate();
		GLuint PreviouseID = VAO.GetID();
		VAO.Delete();

		GLuint ActualID = VAO.GetID();
		GLuint ExpectedID = VertexArray::InvalidID;
		ASSERT_EQ(ActualID, ExpectedID);
	}

}