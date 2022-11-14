#pragma once

#include "Zinet/Core/ZtUniqueIdentifierMaker.h"

#include <gtest/gtest.h>

namespace zt::tests
{

    class UniqueIdentifierMakerTests : public ::testing::Test
    {
    protected:

        UniqueIdentifierMaker uniqueIdentifierMaker;

    };

    TEST_F(UniqueIdentifierMakerTests, ReserveTest)
    {
        Identifier firstUniqueIdentifier = uniqueIdentifierMaker.reserve();
        size_t expectedFirstUnderlyingNumber = 0;
        size_t actualFirstUnderlyingNumber = firstUniqueIdentifier.getUnderlyingNumber();

        ASSERT_EQ(actualFirstUnderlyingNumber, expectedFirstUnderlyingNumber);

        Identifier secondUniqueIdentifier = uniqueIdentifierMaker.reserve();
        size_t expectedSecondUnderlyingNumber = 1;
        size_t actualSecondUnderlyingNumber = secondUniqueIdentifier.getUnderlyingNumber();

        ASSERT_EQ(actualSecondUnderlyingNumber, expectedSecondUnderlyingNumber);
    }

    TEST_F(UniqueIdentifierMakerTests, ReleaseTest)
    {
        Identifier firstUniqueIdentifier = uniqueIdentifierMaker.reserve();
        uniqueIdentifierMaker.release(firstUniqueIdentifier);

        Identifier secondUniqueIdentifier = uniqueIdentifierMaker.reserve();
        size_t expectedSecondUnderlyingNumber = 0;
        size_t actualSecondUnderlyingNumber = secondUniqueIdentifier.getUnderlyingNumber();

        ASSERT_EQ(actualSecondUnderlyingNumber, expectedSecondUnderlyingNumber);
    }

    TEST_F(UniqueIdentifierMakerTests, IsReservedTrueTest)
    {
        Identifier uid = uniqueIdentifierMaker.reserve();
        bool isReserved = uniqueIdentifierMaker.isReserved(uid.getUnderlyingNumber());
        ASSERT_TRUE(isReserved);
    }

    TEST_F(UniqueIdentifierMakerTests, IsReservedFalseTest)
    {
        bool isReserved = uniqueIdentifierMaker.isReserved(0);
        ASSERT_FALSE(isReserved);
    }

}