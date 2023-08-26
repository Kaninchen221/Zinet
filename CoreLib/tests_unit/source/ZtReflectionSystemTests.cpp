#pragma once

#include "Zinet/Core/Reflection/ZtReflectionSystem.h"

#include <gtest/gtest.h>

namespace zt::core::tests
{

    class ReflectionSystemTests : public ::testing::Test
    {
    protected:



    };

    TEST_F(ReflectionSystemTests, ReflectSomething)
    {
		static_assert(std::is_same_v<decltype(ReflectedData::name), std::string>);
		static_assert(std::is_same_v<decltype(ReflectedData::typeName), std::string>);
		static_assert(std::is_same_v<decltype(ReflectedData::address), void*>);

        int variable{};
        std::string expectedName = "variable";
        ReflectedData reflectedData = ReflectionSystem::Reflect(variable, expectedName);
		EXPECT_EQ(reflectedData.name, expectedName);

		std::string expectedTypeName = "int";
		EXPECT_EQ(reflectedData.typeName, expectedTypeName);

		EXPECT_EQ(reflectedData.address, &variable);
    }

}