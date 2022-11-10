
// TODO Clean/Remove that files
//#include "ZtElementBufferTests.h"
//#include "ZtVertexArrayTests.h"
//#include "ZtTextureTests.h"
//#include "ZtObjectTests.h"

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

#include "Buffers/ZtGLBufferTests.h"
#include "Buffers/ZtGLVertexBufferTests.h"
#include "Buffers/ZtGLStagingBufferTests.h"
#include "ZtGLDeviceMemoryTests.h"
#include "Buffers/ZtGLIndexBufferTests.h"
#include "Buffers/ZtGLUniformBufferTests.h"
#include "ZtGLImageTests.h"
#include "Buffers/ZtGLImageBufferTests.h"
#include "ZtGLVmaTests.h"
#include "ZtGLSamplerTests.h"
#include "ZtGLRendererTests.h"

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

int main(int argc, char* argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
    auto runAllTestsResult = RUN_ALL_TESTS();

    return runAllTestsResult;
}