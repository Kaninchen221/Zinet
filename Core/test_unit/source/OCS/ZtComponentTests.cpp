#pragma once

#include "Zinet/Core/OCS/ZtComponent.h"

#include <gtest/gtest.h>

namespace zt::core::tests
{

    class ComponentTests : public ::testing::Test
    {
    protected:

        zt::core::Component Component;

    };

    TEST_F(ComponentTests, PassTest)
    {
    }

}