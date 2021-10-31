
#include "gtest/gtest.h"

#include "ZtWindowTests.h"
#include "ZtShaderTests.h"
#include "ZtShaderTypeTests.h"
#include "ZtVertexTests.h"
#include "ZtProgramTests.h"
#include "ZtVertexBufferTests.h"
#include "ZtElementBufferTests.h"
#include "ZtVertexArrayTests.h"
#include "ZtTextureTests.h"
#include "ZtObjectTests.h"
#include "ZtGLContextTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}