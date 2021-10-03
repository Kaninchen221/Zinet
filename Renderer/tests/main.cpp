
#include "gtest/gtest.h"

#include "ZtWindowTests.h"
#include "ZtShaderTests.h"
#include "ZtShaderTypeTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}