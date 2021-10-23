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

TEST_F(ZtVertexTests, ConstructorVec3Test)
{
	glm::vec3 ExpectedPosition = { 34.f, 0.f, 2.323f };
	ZtVertex Vertex(ExpectedPosition);

	glm::vec3 ActualPosition = Vertex.GetPosition();
	glm::bvec3 AreEqual = glm::equal(ExpectedPosition, ActualPosition);
	ASSERT_TRUE(glm::all(AreEqual));
}