#define ZINET_COLLECT_ALLOCATION_DEBUG_DATA
#include "Zinet/Core/ZtAllocationDebugStatistics.h"

#include <gtest/gtest.h>

#include "Zinet/Core/ZtLogger.h"

int main(int argc, char* argv[]) 
{
	auto callback = []() { FAIL() << "Some logger log error, warning or critical"; };
	zt::CustomSink<>::SetFailTestCallback(callback);

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}