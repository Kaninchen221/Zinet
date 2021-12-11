#pragma once

#include "Zinet/Core/OCS/ZtComponent.h"

#include "gtest/gtest.h"

namespace zt::tests
{

    class ComponentTests : public ::testing::Test
    {
    protected:

        zt::Component Component;

    };

    TEST_F(ComponentTests, PassTest)
    {
    }

}