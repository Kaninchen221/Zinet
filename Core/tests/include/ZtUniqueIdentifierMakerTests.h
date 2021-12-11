#pragma once

#include "Zinet/Core/ZtUniqueIdentifierMaker.h"

#include "gtest/gtest.h"

namespace zt::tests
{

    class UniqueIdentifierMakerTests : public ::testing::Test
    {
    protected:

        UniqueIdentifierMaker UniqueIdentifierMaker;

    };

    TEST_F(UniqueIdentifierMakerTests, ReserveTest)
    {
        Identifier FirstUniqueIdentifier = UniqueIdentifierMaker.Reserve();
        size_t ExpectedFirstUnderlyingNumber = 0;
        size_t ActualFirstUnderlyingNumber = FirstUniqueIdentifier.GetUnderlyingNumber();

        ASSERT_EQ(ActualFirstUnderlyingNumber, ExpectedFirstUnderlyingNumber);

        Identifier SecondUniqueIdentifier = UniqueIdentifierMaker.Reserve();
        size_t ExpectedSecondUnderlyingNumber = 1;
        size_t ActualSecondUnderlyingNumber = SecondUniqueIdentifier.GetUnderlyingNumber();

        ASSERT_EQ(ActualSecondUnderlyingNumber, ExpectedSecondUnderlyingNumber);
    }

    TEST_F(UniqueIdentifierMakerTests, ReleaseTest)
    {
        Identifier FirstUniqueIdentifier = UniqueIdentifierMaker.Reserve();
        UniqueIdentifierMaker.Release(FirstUniqueIdentifier);

        Identifier SecondUniqueIdentifier = UniqueIdentifierMaker.Reserve();
        size_t ExpectedSecondUnderlyingNumber = 0;
        size_t ActualSecondUnderlyingNumber = SecondUniqueIdentifier.GetUnderlyingNumber();

        ASSERT_EQ(ActualSecondUnderlyingNumber, ExpectedSecondUnderlyingNumber);
    }

    TEST_F(UniqueIdentifierMakerTests, IsReservedTrueTest)
    {
        Identifier UID = UniqueIdentifierMaker.Reserve();
        bool IsReserved = UniqueIdentifierMaker.IsReserved(UID.GetUnderlyingNumber());
        ASSERT_TRUE(IsReserved);
    }

    TEST_F(UniqueIdentifierMakerTests, IsReservedFalseTest)
    {
        bool IsReserved = UniqueIdentifierMaker.IsReserved(0);
        ASSERT_FALSE(IsReserved);
    }

}