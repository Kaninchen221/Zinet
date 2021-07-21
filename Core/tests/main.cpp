
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
#include "Reflection/ZtReflectedClassMacroTests.h"
#include "Reflection/ZtReflectedClassTests.h"
#include "Reflection/ZtReflectedMemberFunctionMacroTests.h"
#include "Reflection/ZtReflectedMemberFunctionTests.h"
#include "Reflection/ZtReflectedMemberPropertyMacroTests.h"
#include "Reflection/ZtReflectedMemberPropertyTests.h"
#include "Reflection/ZtReflectionRegistryTests.h"
#include "Reflection/ZtReflectionUtilitiesTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}