
#include "gtest/gtest.h"

#include "ZtLogger-tests.h"
#include "ZtMainException-tests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}