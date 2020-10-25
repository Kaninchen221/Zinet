#pragma once

#include "gtest/gtest.h"

#include "mocks/ZtSystemMock.h"

class ZtSystemTests : public ::testing::Test {
protected:

    ZtSystemTests() {
    }

    ~ZtSystemTests() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

};

TEST_F(ZtSystemTests, ConstructorTest) {

    ZtSystemMock system;

}