#pragma once

#include "Zinet/GraphicLayer/ZtElementBuffer.h"
#include "Zinet/GraphicLayer/ZtVertex.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

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

		ElementBuffer VBO;

		Window Window;

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
		GLuint NotExpectedID = ElementBuffer::InvalidID;
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
		std::array<Vertex, 1> Vertices;
		VBO.SetData<std::array<Vertex, 1>>(Vertices, BufferUsage::Static);
	}

	TEST_F(ZtElementBufferTests, InvalidIDTest)
	{
		GLuint ActualInvalidID = ElementBuffer::InvalidID;
		GLuint ExpectedInvalidID = 0u;

		ASSERT_EQ(ActualInvalidID, ExpectedInvalidID);
	}

	TEST_F(ZtElementBufferTests, DeleteTest)
	{
		VBO.Generate();
		VBO.Delete();

		GLuint ActualID = VBO.GetID();
		GLuint ExpectedID = ElementBuffer::InvalidID;

		ASSERT_EQ(ActualID, ExpectedID);
	}

}