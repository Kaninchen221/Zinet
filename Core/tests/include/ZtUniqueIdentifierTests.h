#pragma once

#include "Zinet/Core/ZtUniqueIdentifier.h"

#include "gtest/gtest.h"

#include <type_traits>

class ZtUniqueIdentifierTests : public ::testing::Test
{
protected:

};

TEST_F(ZtUniqueIdentifierTests, ConstructibleTests)
{
    static_assert(std::is_constructible_v<ZtUniqueIdentifier, std::int64_t>);
    static_assert(!std::is_default_constructible_v<ZtUniqueIdentifier>);
    static_assert(!std::is_copy_constructible_v<ZtUniqueIdentifier>);
    static_assert(!std::is_move_constructible_v<ZtUniqueIdentifier>);
}

TEST_F(ZtUniqueIdentifierTests, AssignableTests)
{
    static_assert(!std::is_copy_assignable_v<ZtUniqueIdentifier>);
    static_assert(!std::is_move_assignable_v<ZtUniqueIdentifier>);
}

TEST_F(ZtUniqueIdentifierTests, GetUnderlyingNumberTest)
{
    size_t ExpectedUnderlyingNumber = 45;
    ZtUniqueIdentifier UniqueIdentifier(ExpectedUnderlyingNumber);

    size_t ActualUnderlyingNumber = UniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualUnderlyingNumber, ExpectedUnderlyingNumber);
}
