#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ZtMainException.h"

class ZtMainExceptionTests : public ::testing::Test {
protected:

};

TEST_F(ZtMainExceptionTests, CatchAsZtMainException) {

    std::string message = "Exception Message";

    try {
        throw zt::MainException(message);
    }
    catch (const zt::MainException& mainEx) {
        ASSERT_EQ(message, mainEx.message());
    }
    catch (...) {
        FAIL() << "Must be catched as zt::MainException";
    }

}

TEST_F(ZtMainExceptionTests, CatchAsStdException) {

    std::string message = "Exception Message";

    try {
        throw zt::MainException(message);
    }
    catch (const std::exception& ex) {
        ASSERT_EQ(message, ex.what());
    }
    catch (...) {
        FAIL() << "Must be catched as std::exception";
    }

}