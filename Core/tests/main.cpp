
#include "gtest/gtest.h"

#include "ZtClockTests.h"
#include "ZtTimeTests.h"
#include "ZtFileFinderTests.h"
#include "ZtWorldTests.h"
#include "ZtLevelTests.h"
#include "ZtPointerTests.h"
#include "ZtRendererTests.h"
#include "ZtEventDispatcherTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}