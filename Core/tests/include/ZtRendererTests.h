#pragma once

#include "Zinet/Core/ZtRenderer.h"

#include "gtest/gtest.h"

class ZtRendererTests : public ::testing::Test
{
protected:

	ZtRenderer Renderer;
};


TEST_F(ZtRendererTests, DrawTest)
{
    ZtSprite Sprite;
    Renderer.DrawSprite(Sprite);
}