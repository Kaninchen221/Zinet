#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ECRS/ZtSystem.h"

class ZtSystemTests : public ::testing::Test {
protected:

    using DefaultSystem = zt::System<zt::Component>;
    using Components = DefaultSystem::ComponentsContainer;

    ZtSystemTests() {
    }

    ~ZtSystemTests() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

};

TEST_F(ZtSystemTests, updateMustThrowExceptionTest) {

    DefaultSystem system;
    Components components;
    zt::Time::Microseconds elapsedTime{};
    
    ASSERT_ANY_THROW(system.update(components, elapsedTime));
}


