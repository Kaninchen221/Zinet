#include <gtest/gtest.h>

int main(int argc, char* argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    auto runAllTestsResult = RUN_ALL_TESTS();

    return runAllTestsResult;
}