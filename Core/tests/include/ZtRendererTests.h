#pragma once

#include "Zinet/Core/ZtRenderer.h"
#include "Zinet/Core/ZtRenderInfo.h"

#include "SFML/Graphics/RenderTexture.hpp"

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
	ZtRenderInfo RenderInfo
	{
		plf::colony<sf::Vertex>(),
		sf::PrimitiveType::Points,
		sf::Transform(),
		sf::Texture(),
		sf::IntRect(),
		sf::BlendMode(),
		sf::Shader()
	};

	Renderer.Draw(RenderInfo);
}