#pragma once

#include "Zinet/Core/OCS/ZtSystem.h"

#include <gtest/gtest.h>

namespace zt::tests
{

    class SystemTests : public ::testing::Test
    {
    protected:

        System System;

    };

    TEST_F(SystemTests, PassTest)
    {

    }

}