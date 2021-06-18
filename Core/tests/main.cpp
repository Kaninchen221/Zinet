
#include "gtest/gtest.h"

#include "ZtClockTests.h"
#include "ZtTimeTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}