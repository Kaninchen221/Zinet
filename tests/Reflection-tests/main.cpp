
#include "gtest/gtest.h"

#include "ZtReflectionException-tests.h"
#include "ZtReflectionRegister-tests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}