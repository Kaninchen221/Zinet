#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtSprite.h"

class ZtSpriteTests : public ::testing::Test
{
protected:

	ZtSprite Sprite;

};

TEST_F(ZtSpriteTests, RenderTypeTest)
{
    Sprite.SetRenderType(ZtRenderType::Dynamic);
    ZtRenderType ActualRenderType = Sprite.GetRenderType();
    ZtRenderType ExpectedRenderType = ZtRenderType::Dynamic;

    ASSERT_EQ(ActualRenderType, ExpectedRenderType);
}