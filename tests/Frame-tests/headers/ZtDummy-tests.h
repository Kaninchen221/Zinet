#pragma once

#include "Zinet/Frame/ZtDummy.h"

#include "gtest/gtest.h"

class ZtDummyTests : public ::testing::Test {
protected:

};

TEST_F(ZtDummyTests, passTest) {

    bool trueValue = true;
    ASSERT_TRUE(trueValue);

}

TEST_F(ZtDummyTests, fooTest) {

    zt::Dummy dummy;
    dummy.foo();

}