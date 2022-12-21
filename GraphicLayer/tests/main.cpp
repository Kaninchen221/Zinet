
#include "ZtGLVertexTests.h"
#include "ZtGLVulkanObjectTests.h"
#include "ZtGLShaderTypeTests.h"
#include "ZtGLShaderTests.h"
#include "ZtGLShaderModuleTests.h"
#include "ZtGLWindowTests.h"
#include "ZtGLGLFWTests.h"
#include "ZtGLContextTests.h"
#include "ZtGLInstanceTests.h"
#include "ZtGLDebugUtilsMessengerTests.h"
#include "ZtGLPhysicalDeviceTests.h"
#include "ZtGLDeviceTests.h"
#include "ZtGLQueueTests.h"
#include "ZtGLSurfaceTests.h"
#include "ZtGLSwapChainSupportDetailsTests.h"
#include "ZtGLSwapChainTests.h"
#include "ZtGLImageViewTests.h"
#include "ZtGLRenderPassTests.h"
#include "ZtGLPipelineLayoutTests.h"
#include "ZtGLPipelineTests.h"
#include "ZtGLFramebufferTests.h"
#include "ZtGLCommandPoolTests.h"
#include "ZtGLCommandBufferTests.h"
#include "ZtGLSemaphoreTests.h"
#include "ZtGLFenceTests.h"
#include "ZtGLDescriptorSetLayoutTests.h"
#include "ZtGLDescriptorPoolTests.h"
#include "ZtGLDescriptorSetsTests.h"
#include "ZtGLSTBImageTests.h"
#include "ZtGLVmaTests.h"
#include "ZtGLSamplerTests.h"
#include "ZtGLImageTests.h"
#include "ZtGLRendererTests.h"
#include "ZtGLDrawInfoTests.h"

#include "Buffers/ZtGLBufferTests.h"
#include "Buffers/ZtGLVertexBufferTests.h"
#include "Buffers/ZtGLStagingBufferTests.h"
#include "Buffers/ZtGLIndexBufferTests.h"
#include "Buffers/ZtGLUniformBufferTests.h"
#include "Buffers/ZtGLImageBufferTests.h"

// Input events related classes
#include "ZtGLEventTests.h"
#include "ZtGLKeyboardTests.h"
#include "ZtGLKeyboardKeyTests.h"
#include "ZtGLKeyboardEventTests.h"
#include "ZtGLKeyboardEventTypeTests.h"
#include "ZtGLMouseTests.h"
#include "ZtGLMouseButtonEventTests.h"
#include "ZtGLMouseButtonTests.h"
#include "ZtGLMouseButtonEventTypeTests.h"
#include "ZtGLMousePositionEventTests.h"

#include <gtest/gtest.h>

#include "ZtGLRendererBuilder.h"

int main(int argc, char* argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    auto runAllTestsResult = RUN_ALL_TESTS();

    //int runAllTestsResult = 0;
    zt::gl::tests::RendererBuilder rb;
    zt::gl::GLFW::UnhideWindow();
    rb.createAll();
    rb.run();

    return runAllTestsResult;
}