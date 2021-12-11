#pragma once

#include "Zinet/Core/ZtIdentifier.h"

#include "gtest/gtest.h"

#include <type_traits>

namespace zt::tests
{

    class IdentifierTests : public ::testing::Test
    {
    protected:

    };

    TEST_F(IdentifierTests, CopyTest)
    {
        size_t ExpectedSecondIDUnderlyingNumber = 23;
        Identifier FirstID(ExpectedSecondIDUnderlyingNumber);
        Identifier SecondID(FirstID);

        size_t ActualSecondIDUnderlyingNumber = SecondID.GetUnderlyingNumber();
        ASSERT_EQ(ActualSecondIDUnderlyingNumber, ExpectedSecondIDUnderlyingNumber);

        size_t ActualFirstIDUnderlyingNumber = FirstID.GetUnderlyingNumber();
        ASSERT_EQ(ActualFirstIDUnderlyingNumber, Identifier::Invalid);
    }

    TEST_F(IdentifierTests, MoveTest)
    {
        size_t ExpectedSecondIDUnderlyingNumber = 23;
        Identifier FirstID(ExpectedSecondIDUnderlyingNumber);
        Identifier SecondID(std::move(FirstID));

        size_t ActualSecondIDUnderlyingNumber = SecondID.GetUnderlyingNumber();
        ASSERT_EQ(ActualSecondIDUnderlyingNumber, ExpectedSecondIDUnderlyingNumber);

        size_t ActualFirstIDUnderlyingNumber = FirstID.GetUnderlyingNumber();
        ASSERT_EQ(ActualFirstIDUnderlyingNumber, Identifier::Invalid);
    }

    TEST_F(IdentifierTests, GetUnderlyingNumberTest)
    {
        size_t ExpectedUnderlyingNumber = 45;
        Identifier UniqueIdentifier(ExpectedUnderlyingNumber);

        size_t ActualUnderlyingNumber = UniqueIdentifier.GetUnderlyingNumber();

        ASSERT_EQ(ActualUnderlyingNumber, ExpectedUnderlyingNumber);
    }

}