#pragma once

#include "Zinet/Core/ZtIdentifier.h"

#include "gtest/gtest.h"

#include <type_traits>

class ZtIdentifierTests : public ::testing::Test
{
protected:

};

TEST_F(ZtIdentifierTests, CopyTest)
{
    size_t ExpectedSecondIDUnderlyingNumber = 23;
    ZtIdentifier FirstID(ExpectedSecondIDUnderlyingNumber);
    ZtIdentifier SecondID(FirstID);

    size_t ActualSecondIDUnderlyingNumber = SecondID.GetUnderlyingNumber();
    ASSERT_EQ(ActualSecondIDUnderlyingNumber, ExpectedSecondIDUnderlyingNumber);

    size_t ActualFirstIDUnderlyingNumber = FirstID.GetUnderlyingNumber();
    ASSERT_EQ(ActualFirstIDUnderlyingNumber, ZtIdentifier::Invalid);
}

TEST_F(ZtIdentifierTests, MoveTest)
{
    size_t ExpectedSecondIDUnderlyingNumber = 23;
    ZtIdentifier FirstID(ExpectedSecondIDUnderlyingNumber);
    ZtIdentifier SecondID(std::move(FirstID));

    size_t ActualSecondIDUnderlyingNumber = SecondID.GetUnderlyingNumber();
    ASSERT_EQ(ActualSecondIDUnderlyingNumber, ExpectedSecondIDUnderlyingNumber);

    size_t ActualFirstIDUnderlyingNumber = FirstID.GetUnderlyingNumber();
    ASSERT_EQ(ActualFirstIDUnderlyingNumber, ZtIdentifier::Invalid);
}

TEST_F(ZtIdentifierTests, GetUnderlyingNumberTest)
{
    size_t ExpectedUnderlyingNumber = 45;
    ZtIdentifier UniqueIdentifier(ExpectedUnderlyingNumber);

    size_t ActualUnderlyingNumber = UniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualUnderlyingNumber, ExpectedUnderlyingNumber);
}
