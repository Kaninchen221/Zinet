
#include "gtest/gtest.h"

#include "ZtClockTests.h"
#include "ZtTimeTests.h"
#include "ZtFileFinderTests.h"
#include "ZtWorldTests.h"
#include "ZtLevelTests.h"
#include "ZtRendererTests.h"
#include "ZtEventBroadcasterTests.h"
#include "ZtEntityTests.h"
#include "ZtComponentTests.h"
#include "ZtSystemTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}