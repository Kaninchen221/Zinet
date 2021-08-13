#pragma once

#include "Zinet/Core/ZtUniqueIdentifierMaker.h"

#include "gtest/gtest.h"

class ZtUniqueIdentifierMakerTests : public ::testing::Test
{
protected:

    ZtUniqueIdentifierMaker UniqueIdentifierMaker;

};

TEST_F(ZtUniqueIdentifierMakerTests, ReserveTest)
{
    ZtIdentifier FirstUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    size_t ExpectedFirstUnderlyingNumber = 0;
    size_t ActualFirstUnderlyingNumber = FirstUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualFirstUnderlyingNumber, ExpectedFirstUnderlyingNumber);

    ZtIdentifier SecondUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    size_t ExpectedSecondUnderlyingNumber = 1;
    size_t ActualSecondUnderlyingNumber = SecondUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualSecondUnderlyingNumber, ExpectedSecondUnderlyingNumber);
}

TEST_F(ZtUniqueIdentifierMakerTests, ReleaseTest)
{
    ZtIdentifier FirstUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    UniqueIdentifierMaker.Release(FirstUniqueIdentifier);

    ZtIdentifier SecondUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    size_t ExpectedSecondUnderlyingNumber = 0;
    size_t ActualSecondUnderlyingNumber = SecondUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualSecondUnderlyingNumber, ExpectedSecondUnderlyingNumber);
}

TEST_F(ZtUniqueIdentifierMakerTests, IsReservedTrueTest)
{
    ZtIdentifier UID = UniqueIdentifierMaker.Reserve();
    bool IsReserved = UniqueIdentifierMaker.IsReserved(UID.GetUnderlyingNumber());
    ASSERT_TRUE(IsReserved);
}

TEST_F(ZtUniqueIdentifierMakerTests, IsReservedFalseTest)
{
    bool IsReserved = UniqueIdentifierMaker.IsReserved(0);
    ASSERT_FALSE(IsReserved);
}