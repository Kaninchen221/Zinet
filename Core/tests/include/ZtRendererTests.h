#pragma once

#include "Zinet/Core/ZtRenderer.h"
#include "Zinet/Core/ZtRenderInfo.h"

#include "SFML/Graphics/RenderTexture.hpp"

#include <array>

#include "gtest/gtest.h"

class ZtRendererTests : public ::testing::Test
{
protected:

	ZtRenderer Renderer;
};

TEST_F(ZtRendererTests, SetGetRenderTargetTest)
{
	sf::RenderTexture ExpectedRenderTarget;
	
	Renderer.SetRenderTarget(&ExpectedRenderTarget);
	ZtRenderTarget* ActualRenderTarget = Renderer.GetRenderTarget();

	ASSERT_EQ(ActualRenderTarget, &ExpectedRenderTarget);
}

TEST_F(ZtRendererTests, DrawTest)
{
	std::array<sf::Vertex, 0> Vertices;

	ZtRenderInfo RenderInfo
	{
		Vertices.data(),
		0u,
		sf::PrimitiveType::Points,
		sf::IntRect(),
		sf::RenderStates::Default
	};

	Renderer.Draw(RenderInfo);
}