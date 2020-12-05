
#include "gtest/gtest.h"

#include "ZtLoop-tests.h"
#include "ZtFrameException-tests.h"
#include "ZtWindow-tests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}