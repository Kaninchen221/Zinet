#pragma once

#include "Zinet/GraphicLayer/ZtGLVertex.h"

#include "gtest/gtest.h"

#include "glm/vector_relational.hpp"

namespace zt::gl::tests
{

	class VertexTests : public ::testing::Test
	{
	protected:

		Vertex vertex{};

	};

	TEST_F(VertexTests, GetPosition)
	{
		glm::vec3 position = vertex.getPosition();
	}

	TEST_F(VertexTests, SetPosition)
	{
		glm::vec3 expectedPosition = { 1.f, 0.34f, 0.f };
		vertex.setPosition(expectedPosition);

		glm::vec3 actualPosition = vertex.getPosition();
		glm::bvec3 areEqual = glm::equal(expectedPosition, actualPosition);
		ASSERT_TRUE(glm::all(areEqual));
	}

	TEST_F(VertexTests, GetColor)
	{
		glm::vec4 color = vertex.getColor();
	}

	TEST_F(VertexTests, SetColor)
	{
		glm::vec4 expectedColor = { 1.34f, 0.21f, 0.f, 1.f };
		vertex.setColor(expectedColor);

		glm::vec4 actualColor = vertex.getColor();
		glm::bvec4 areEqual = glm::equal(expectedColor, actualColor);
		ASSERT_TRUE(glm::all(areEqual));
	}

	TEST_F(VertexTests, GetTextureCoordinates)
	{
		glm::vec2 textureCoordinates = vertex.getTextureCoordinates();
	}

	TEST_F(VertexTests, SetTextureCoordinates)
	{
		glm::vec2 expectedTextureCoordinates = { 1.0f, 0.0f };
		vertex.setTextureCoordinates(expectedTextureCoordinates);

		glm::vec2 actualTextureCoordinates = vertex.getTextureCoordinates();
		glm::bvec2 areEqual = glm::equal(expectedTextureCoordinates, actualTextureCoordinates);
		ASSERT_TRUE(glm::all(areEqual));
	}

	TEST_F(VertexTests, ParamConstructor)
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

	TEST_F(VertexTests, GetOffsetToPosition)
	{
		std::size_t actualOffset = Vertex::GetOffsetToPosition();
		std::size_t expectedOffset = 0;

		ASSERT_EQ(actualOffset, expectedOffset);
	}

	TEST_F(VertexTests, GetOffsetToColor)
	{
		std::size_t actualOffset = Vertex::GetOffsetToColor();
		std::size_t expectedOffset = sizeof(decltype(vertex.getPosition()));

		ASSERT_EQ(actualOffset, expectedOffset);
	}

	TEST_F(VertexTests, GetOffsetToTextureCoordinates)
	{
		std::size_t actualOffset = Vertex::GetOffsetToTextureCoordinates();
		std::size_t expectedOffset = sizeof(decltype(vertex.getPosition())) + sizeof(decltype(vertex.getColor()));

		ASSERT_EQ(actualOffset, expectedOffset);
	}

	TEST_F(VertexTests, CreateInputBindingDescription)
	{
		vk::VertexInputBindingDescription vertexInputBindingDescription = Vertex::CreateInputBindingDescription();

		ASSERT_NE(vertexInputBindingDescription, vk::VertexInputBindingDescription{});
	}

	TEST_F(VertexTests, CreatePositionInputAttributeDescription)
	{
		vk::VertexInputAttributeDescription description = Vertex::CreatePositionInputAttributeDescription();

		ASSERT_EQ(description.binding, 0);
		ASSERT_EQ(description.location, 0);
		ASSERT_EQ(description.format, vk::Format::eR32G32B32Sfloat);
		ASSERT_EQ(description.offset, 0);
	}

	TEST_F(VertexTests, CreateColorInputAttributeDescription)
	{
		vk::VertexInputAttributeDescription description = Vertex::CreateColorInputAttributeDescription();

		ASSERT_EQ(description.binding, 0);
		ASSERT_EQ(description.location, 1);
		ASSERT_EQ(description.format, vk::Format::eR32G32B32A32Sfloat);
		ASSERT_EQ(description.offset, sizeof(glm::vec3));
	}

	TEST_F(VertexTests, CreateTextureCoordinatesInputAttributeDescription)
	{
		vk::VertexInputAttributeDescription description = Vertex::CreateTextureCoordinatesInputAttributeDescription();

		ASSERT_EQ(description.binding, 0);
		ASSERT_EQ(description.location, 2);
		ASSERT_EQ(description.format, vk::Format::eR32G32Sfloat);
		ASSERT_EQ(description.offset, sizeof(glm::vec3) + sizeof(glm::vec4));
	}

	TEST_F(VertexTests, ComparisonOperator)
	{
		Vertex vertexFirst{};
		Vertex vertexSecond{};

		ASSERT_EQ(vertexFirst, vertexSecond);

		vertexFirst.setPosition({ 234.3f, 1.f, 2.f });

		ASSERT_NE(vertexFirst, vertexSecond);
	}
}