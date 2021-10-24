#pragma once

#include "Zinet/Renderer/ZtVertex.h"

#include "gtest/gtest.h"

#include "vector_relational.hpp"

class ZtVertexTests : public ::testing::Test
{
protected:

	ZtVertex Vertex{};

};

TEST_F(ZtVertexTests, GetPositionTest)
{
	glm::vec3 Position = Vertex.GetPosition();
}

TEST_F(ZtVertexTests, SetPositionTest)
{
	glm::vec3 ExpectedPosition = { 1.f, 0.34f, 0.f };
	Vertex.SetPosition(ExpectedPosition);

	glm::vec3 ActualPosition = Vertex.GetPosition();
	glm::bvec3 AreEqual = glm::equal(ExpectedPosition, ActualPosition);
	ASSERT_TRUE(glm::all(AreEqual));
}

TEST_F(ZtVertexTests, GetColorTest)
{
	glm::vec4 Color = Vertex.GetColor();
}

TEST_F(ZtVertexTests, SetColorTest)
{
	glm::vec4 ExpectedColor = { 1.34f, 0.21f, 0.f, 1.f };
	Vertex.SetColor(ExpectedColor);

	glm::vec4 ActualColor = Vertex.GetColor();
	glm::bvec4 AreEqual = glm::equal(ExpectedColor, ActualColor);
	ASSERT_TRUE(glm::all(AreEqual));
}

TEST_F(ZtVertexTests, GetTextureCoordinatesTest)
{
	glm::vec2 TextureCoordinates = Vertex.GetTextureCoordinates();
}

TEST_F(ZtVertexTests, SetTextureCoordinatesTest)
{
	glm::vec2 ExpectedTextureCoordinates = { 1.0f, 0.0f };
	Vertex.SetTextureCoordinates(ExpectedTextureCoordinates);

	glm::vec2 ActualTextureCoordinates = Vertex.GetTextureCoordinates();
	glm::bvec2 AreEqual = glm::equal(ExpectedTextureCoordinates, ActualTextureCoordinates);
	ASSERT_TRUE(glm::all(AreEqual));
}

TEST_F(ZtVertexTests, ParamConstructorTest)
{
	glm::vec3 ExpectedPosition = { 34.f, 0.f, 2.323f };
	glm::vec4 ExpectedColor = { 4.f, 0.23f, 211.35f, 1.f };
	glm::vec2 ExpectedTextureCoordinates = { 1.f, 0.f };
	ZtVertex Vertex(ExpectedPosition, ExpectedColor, ExpectedTextureCoordinates);

	glm::vec3 ActualPosition = Vertex.GetPosition();
	glm::bvec3 ArePositionsEqual = glm::equal(ExpectedPosition, ActualPosition);
	ASSERT_TRUE(glm::all(ArePositionsEqual));

	glm::vec4 ActualColor = Vertex.GetColor();
	glm::bvec4 AreColorsEqual = glm::equal(ExpectedColor, ActualColor);
	ASSERT_TRUE(glm::all(AreColorsEqual));

	glm::vec2 ActualTextureCoordinates = Vertex.GetTextureCoordinates();
	glm::bvec2 AreTextureCoordinatesEqual = glm::equal(ExpectedTextureCoordinates, ActualTextureCoordinates);
	ASSERT_TRUE(glm::all(AreTextureCoordinatesEqual));
}