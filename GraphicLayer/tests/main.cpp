
//#include "ZtElementBufferTests.h"
//#include "ZtVertexArrayTests.h"
//#include "ZtTextureTests.h"
//#include "ZtObjectTests.h"

#include "ZtGLRendererBuilder.h"

//#include "ZtGLVertexTests.h"
//#include "ZtGLVulkanObjectTests.h"
//#include "ZtGLShaderTypeTests.h"
//#include "ZtGLShaderTests.h"
//#include "ZtGLShaderModuleTests.h"
//#include "ZtGLWindowTests.h"
//#include "ZtGLGLFWTests.h"
//#include "ZtGLContextTests.h"
//#include "ZtGLInstanceTests.h"
//#include "ZtGLDebugUtilsMessengerTests.h"
//#include "ZtGLPhysicalDeviceTests.h"
//#include "ZtGLDeviceTests.h"
//#include "ZtGLQueueTests.h"
//#include "ZtGLSurfaceTests.h"
//#include "ZtGLSwapChainSupportDetailsTests.h"
//#include "ZtGLSwapChainTests.h"
//#include "ZtGLImageViewTests.h"
//#include "ZtGLRenderPassTests.h"
//#include "ZtGLPipelineLayoutTests.h"
//#include "ZtGLPipelineTests.h"
//#include "ZtGLFramebufferTests.h"
//#include "ZtGLCommandPoolTests.h"
//#include "ZtGLCommandBufferTests.h"
//#include "ZtGLSemaphoreTests.h"
//#include "ZtGLFenceTests.h"
//#include "ZtGLBufferTests.h"
//#include "ZtGLVertexBufferTests.h"
//#include "ZtGLStagingBufferTests.h"
//#include "ZtGLDeviceMemoryTests.h"
//#include "ZtGLBufferCopyTests.h"
//#include "ZtGLIndexBufferTests.h"
//#include "ZtGLUniformBufferTests.h"
//#include "ZtGLDescriptorSetLayoutTests.h"
//#include "ZtGLDescriptorPoolTests.h"
//#include "ZtGLDescriptorSetsTests.h"
//#include "ZtGLSTBImageTests.h"
//#include "ZtGLImageTests.h"
//#include "ZtGLImageBufferTests.h"
//#include "ZtGLSamplerTests.h"

//#include "ZtGLRendererTests.h"

// TODO Review old files
//#include "ZtEventTests.h"
//#include "ZtKeyboardTests.h"
//#include "ZtKeyboardKeyTests.h"
//#include "ZtKeyboardEventTests.h"
//#include "ZtKeyboardEventTypeTests.h"
//#include "ZtMouseTests.h"
//#include "ZtMouseButtonEventTests.h"
//#include "ZtMouseButtonTests.h"
//#include "ZtMouseButtonEventTypeTests.h"
//#include "ZtMousePositionEventTests.h"

#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
    zt::gl::tests::RendererBuilder rb;
    rb.contentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";
    rb.createAll();
    rb.run();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}