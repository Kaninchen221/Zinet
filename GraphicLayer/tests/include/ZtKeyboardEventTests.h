#pragma once

#include "Zinet/GraphicLayer/ZtKeyboardEvent.h"

#include "gtest/gtest.h"

class ZtKeyboardEventTests : public ::testing::Test
{
protected:

	ZtKeyboardEvent KeyboardEvent{};

};

TEST_F(ZtKeyboardEventTests, TypeTest)
{
	ZtKeyboardEventType Type = KeyboardEvent.Type;
}

TEST_F(ZtKeyboardEventTests, KeyTest)
{
	ZtKeyboardKey Key = KeyboardEvent.Key;
}