#pragma once

#include "Zinet/GraphicLayer/ZtVertex.h"

#include "gtest/gtest.h"

#include "glm/vector_relational.hpp"

namespace zt::gl::tests
{

	class ZtVertexTests : public ::testing::Test
	{
	protected:

		Vertex vertex{};

	};

	TEST_F(ZtVertexTests, GetPositionTest)
	{
		glm::vec3 Position = vertex.GetPosition();
	}

	TEST_F(ZtVertexTests, SetPositionTest)
	{
		glm::vec3 ExpectedPosition = { 1.f, 0.34f, 0.f };
		vertex.SetPosition(ExpectedPosition);

		glm::vec3 ActualPosition = vertex.GetPosition();
		glm::bvec3 AreEqual = glm::equal(ExpectedPosition, ActualPosition);
		ASSERT_TRUE(glm::all(AreEqual));
	}

	TEST_F(ZtVertexTests, GetColorTest)
	{
		glm::vec4 Color = vertex.GetColor();
	}

	TEST_F(ZtVertexTests, SetColorTest)
	{
		glm::vec4 ExpectedColor = { 1.34f, 0.21f, 0.f, 1.f };
		vertex.SetColor(ExpectedColor);

		glm::vec4 ActualColor = vertex.GetColor();
		glm::bvec4 AreEqual = glm::equal(ExpectedColor, ActualColor);
		ASSERT_TRUE(glm::all(AreEqual));
	}

	TEST_F(ZtVertexTests, GetTextureCoordinatesTest)
	{
		glm::vec2 TextureCoordinates = vertex.GetTextureCoordinates();
	}

	TEST_F(ZtVertexTests, SetTextureCoordinatesTest)
	{
		glm::vec2 ExpectedTextureCoordinates = { 1.0f, 0.0f };
		vertex.SetTextureCoordinates(ExpectedTextureCoordinates);

		glm::vec2 ActualTextureCoordinates = vertex.GetTextureCoordinates();
		glm::bvec2 AreEqual = glm::equal(ExpectedTextureCoordinates, ActualTextureCoordinates);
		ASSERT_TRUE(glm::all(AreEqual));
	}

	TEST_F(ZtVertexTests, ParamConstructorTest)
	{
		glm::vec3 ExpectedPosition = { 34.f, 0.f, 2.323f };
		glm::vec4 ExpectedColor = { 4.f, 0.23f, 211.35f, 1.f };
		glm::vec2 ExpectedTextureCoordinates = { 1.f, 0.f };
		Vertex vertex(ExpectedPosition, ExpectedColor, ExpectedTextureCoordinates);

		glm::vec3 ActualPosition = vertex.GetPosition();
		glm::bvec3 ArePositionsEqual = glm::equal(ExpectedPosition, ActualPosition);
		ASSERT_TRUE(glm::all(ArePositionsEqual));

		glm::vec4 ActualColor = vertex.GetColor();
		glm::bvec4 AreColorsEqual = glm::equal(ExpectedColor, ActualColor);
		ASSERT_TRUE(glm::all(AreColorsEqual));

		glm::vec2 ActualTextureCoordinates = vertex.GetTextureCoordinates();
		glm::bvec2 AreTextureCoordinatesEqual = glm::equal(ExpectedTextureCoordinates, ActualTextureCoordinates);
		ASSERT_TRUE(glm::all(AreTextureCoordinatesEqual));
	}

	TEST_F(ZtVertexTests, GetOffsetToPositionTest)
	{
		std::size_t ActualOffset = Vertex::GetOffsetToPosition();
		std::size_t ExpectedOffset = 0;

		ASSERT_EQ(ActualOffset, ExpectedOffset);
	}

	TEST_F(ZtVertexTests, GetOffsetToColorTest)
	{
		std::size_t ActualOffset = Vertex::GetOffsetToColor();
		std::size_t ExpectedOffset = sizeof(decltype(vertex.GetPosition()));

		ASSERT_EQ(ActualOffset, ExpectedOffset);
	}

	TEST_F(ZtVertexTests, GetOffsetToTextureCoordinatesTest)
	{
		std::size_t ActualOffset = Vertex::GetOffsetToTextureCoordinates();
		std::size_t ExpectedOffset = sizeof(decltype(vertex.GetPosition())) + sizeof(decltype(vertex.GetColor()));

		ASSERT_EQ(ActualOffset, ExpectedOffset);
	}

}