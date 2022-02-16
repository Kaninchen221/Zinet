
#include "ZtVertexTests.h"
#include "ZtVertexBufferTests.h"
#include "ZtElementBufferTests.h"
#include "ZtVertexArrayTests.h"
#include "ZtTextureTests.h"
#include "ZtObjectTests.h"

#include "ZtGLProgramTests.h"
#include "ZtGLShaderTypeTests.h"
#include "ZtGLShaderTests.h"
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

#include "ZtGLRendererTests.h"

#include "ZtEventTests.h"
#include "ZtKeyboardTests.h"
#include "ZtKeyboardKeyTests.h"
#include "ZtKeyboardEventTests.h"
#include "ZtKeyboardEventTypeTests.h"
#include "ZtMouseTests.h"
#include "ZtMouseButtonEventTests.h"
#include "ZtMouseButtonTests.h"
#include "ZtMouseButtonEventTypeTests.h"
#include "ZtMousePositionEventTests.h"

#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}