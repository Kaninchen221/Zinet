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
    ZtUniqueIdentifier FirstUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    int64_t ExpectedFirstUnderlyingNumber = 0;
    int64_t ActualFirstUnderlyingNumber = FirstUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualFirstUnderlyingNumber, ExpectedFirstUnderlyingNumber);

    ZtUniqueIdentifier SecondUniqueIdentifier = UniqueIdentifierMaker.Reserve();
    int64_t ExpectedSecondUnderlyingNumber = 1;
    int64_t ActualSecondUnderlyingNumber = SecondUniqueIdentifier.GetUnderlyingNumber();

    ASSERT_EQ(ActualSecondUnderlyingNumber, ExpectedSecondUnderlyingNumber);
}