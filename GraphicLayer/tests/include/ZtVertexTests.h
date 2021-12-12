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
		glm::vec3 position = vertex.getPosition();
	}

	TEST_F(ZtVertexTests, SetPositionTest)
	{
		glm::vec3 expectedPosition = { 1.f, 0.34f, 0.f };
		vertex.setPosition(expectedPosition);

		glm::vec3 actualPosition = vertex.getPosition();
		glm::bvec3 areEqual = glm::equal(expectedPosition, actualPosition);
		ASSERT_TRUE(glm::all(areEqual));
	}

	TEST_F(ZtVertexTests, GetColorTest)
	{
		glm::vec4 color = vertex.getColor();
	}

	TEST_F(ZtVertexTests, SetColorTest)
	{
		glm::vec4 expectedColor = { 1.34f, 0.21f, 0.f, 1.f };
		vertex.setColor(expectedColor);

		glm::vec4 actualColor = vertex.getColor();
		glm::bvec4 areEqual = glm::equal(expectedColor, actualColor);
		ASSERT_TRUE(glm::all(areEqual));
	}

	TEST_F(ZtVertexTests, GetTextureCoordinatesTest)
	{
		glm::vec2 textureCoordinates = vertex.getTextureCoordinates();
	}

	TEST_F(ZtVertexTests, SetTextureCoordinatesTest)
	{
		glm::vec2 expectedTextureCoordinates = { 1.0f, 0.0f };
		vertex.setTextureCoordinates(expectedTextureCoordinates);

		glm::vec2 actualTextureCoordinates = vertex.getTextureCoordinates();
		glm::bvec2 areEqual = glm::equal(expectedTextureCoordinates, actualTextureCoordinates);
		ASSERT_TRUE(glm::all(areEqual));
	}

	TEST_F(ZtVertexTests, ParamConstructorTest)
	{
		glm::vec3 expectedPosition = { 34.f, 0.f, 2.323f };
		glm::vec4 expectedColor = { 4.f, 0.23f, 211.35f, 1.f };
		glm::vec2 expectedTextureCoordinates = { 1.f, 0.f };
		Vertex vertex(expectedPosition, expectedColor, expectedTextureCoordinates);

		glm::vec3 actualPosition = vertex.getPosition();
		glm::bvec3 arePositionsEqual = glm::equal(expectedPosition, actualPosition);
		ASSERT_TRUE(glm::all(arePositionsEqual));

		glm::vec4 actualColor = vertex.getColor();
		glm::bvec4 areColorsEqual = glm::equal(expectedColor, actualColor);
		ASSERT_TRUE(glm::all(areColorsEqual));

		glm::vec2 actualTextureCoordinates = vertex.getTextureCoordinates();
		glm::bvec2 areTextureCoordinatesEqual = glm::equal(expectedTextureCoordinates, actualTextureCoordinates);
		ASSERT_TRUE(glm::all(areTextureCoordinatesEqual));
	}

	TEST_F(ZtVertexTests, GetOffsetToPositionTest)
	{
		std::size_t actualOffset = Vertex::GetOffsetToPosition();
		std::size_t expectedOffset = 0;

		ASSERT_EQ(actualOffset, expectedOffset);
	}

	TEST_F(ZtVertexTests, GetOffsetToColorTest)
	{
		std::size_t actualOffset = Vertex::GetOffsetToColor();
		std::size_t expectedOffset = sizeof(decltype(vertex.getPosition()));

		ASSERT_EQ(actualOffset, expectedOffset);
	}

	TEST_F(ZtVertexTests, GetOffsetToTextureCoordinatesTest)
	{
		std::size_t actualOffset = Vertex::GetOffsetToTextureCoordinates();
		std::size_t expectedOffset = sizeof(decltype(vertex.getPosition())) + sizeof(decltype(vertex.getColor()));

		ASSERT_EQ(actualOffset, expectedOffset);
	}

}