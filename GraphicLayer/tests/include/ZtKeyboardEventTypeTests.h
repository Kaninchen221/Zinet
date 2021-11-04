#pragma once

#include "Zinet/GraphicLayer/ZtKeyboardEventType.h"

#include "gtest/gtest.h"

class ZtKeyboardEventTypeTests : public ::testing::Test
{
protected:

	ZtKeyboardEventType KeyboardEventType{};

};

TEST_F(ZtKeyboardEventTypeTests, ConstructionTest)
{}