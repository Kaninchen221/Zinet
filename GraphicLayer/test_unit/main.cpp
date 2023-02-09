#include <gtest/gtest.h>

#include "ZtGLRendererBuilder.h"

int main(int argc, char* argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    auto runAllTestsResult = RUN_ALL_TESTS();

    //int runAllTestsResult = 0;
    //zt::gl::tests::RendererBuilder rb;
    //zt::gl::GLFW::UnhideWindow();
    //rb.createAll();
    //rb.run();

    return runAllTestsResult;
}