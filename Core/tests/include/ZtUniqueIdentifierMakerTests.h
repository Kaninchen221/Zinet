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
    ZtSize ExpectedFirstUnderlyingNumber = 0;
    ZtSize ActualFirstUnderlyingNumber = FirstUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualFirstUnderlyingNumber, ExpectedFirstUnderlyingNumber);

    ZtIdentifier SecondUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    ZtSize ExpectedSecondUnderlyingNumber = 1;
    ZtSize ActualSecondUnderlyingNumber = SecondUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualSecondUnderlyingNumber, ExpectedSecondUnderlyingNumber);
}

TEST_F(ZtUniqueIdentifierMakerTests, ReleaseTest)
{
    ZtIdentifier FirstUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    UniqueIdentifierMaker.Release(FirstUniqueIdentifier);

    ZtIdentifier SecondUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    ZtSize ExpectedSecondUnderlyingNumber = 0;
    ZtSize ActualSecondUnderlyingNumber = SecondUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualSecondUnderlyingNumber, ExpectedSecondUnderlyingNumber);
}

TEST_F(ZtUniqueIdentifierMakerTests, IsReservedTrueTest)
{
    ZtIdentifier UID = UniqueIdentifierMaker.Reserve();
    ZtBool IsReserved = UniqueIdentifierMaker.IsReserved(UID.GetUnderlyingNumber());
    ASSERT_TRUE(IsReserved);
}

TEST_F(ZtUniqueIdentifierMakerTests, IsReservedFalseTest)
{
    ZtBool IsReserved = UniqueIdentifierMaker.IsReserved(0);
    ASSERT_FALSE(IsReserved);
}