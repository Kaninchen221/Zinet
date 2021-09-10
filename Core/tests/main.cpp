
#include "gtest/gtest.h"

#include "OCS/ZtComponentTests.h"
#include "OCS/ZtObjectTests.h"
#include "OCS/ZtSystemTests.h"
#include "Reflection/ZtReflectedClassMacroTests.h"
#include "Reflection/ZtReflectedClassTests.h"
#include "Reflection/ZtReflectedCollectionTests.h"
#include "Reflection/ZtReflectedMemberFunctionMacroTests.h"
#include "Reflection/ZtReflectedMemberFunctionTests.h"
#include "Reflection/ZtReflectedMemberPropertyMacroTests.h"
#include "Reflection/ZtReflectedMemberPropertyTests.h"
#include "Reflection/ZtReflectionUtilitiesTests.h"
#include "ZtClockTests.h"
#include "ZtEventBroadcasterTests.h"
#include "ZtFileFinderTests.h"
#include "ZtIdentifierTests.h"
#include "ZtLevelTests.h"
#include "ZtRendererTests.h"
#include "ZtTimeTests.h"
#include "ZtUniqueIdentifierMakerTests.h"
#include "ZtWorldTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}