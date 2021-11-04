#pragma once

#include "Zinet/GraphicLayer/ZtKeyboardKey.h"

#include "gtest/gtest.h"

class ZtKeyboardKeyTests : public ::testing::Test
{
protected:

	ZtKeyboardKey KeyboardKey{};

};

TEST_F(ZtKeyboardKeyTests, ConstructTest)
{}