
#include "gtest/gtest.h"

#include "ZtClockTests.h"
#include "ZtTimeTests.h"
#include "ZtFileFinderTests.h"
#include "ZtWorldTests.h"
#include "ZtLevelTests.h"
#include "ZtRendererTests.h"
#include "ZtEventBroadcasterTests.h"
#include "ZtUniqueIdentifierMakerTests.h"
#include "ZtUniqueIdentifierTests.h"
#include "OCS/ZtComponentTests.h"
#include "OCS/ZtSystemTests.h"
#include "OCS/ZtObjectTests.h"
#include "Reflection/ZtReflectedClassMacroTests.h"
#include "Reflection/ZtReflectedClassTests.h"
#include "Reflection/ZtReflectedMemberFunctionMacroTests.h"
#include "Reflection/ZtReflectedMemberFunctionTests.h"
#include "Reflection/ZtReflectedMemberPropertyMacroTests.h"
#include "Reflection/ZtReflectedMemberPropertyTests.h"
#include "Reflection/ZtReflectedCollectionTests.h"
#include "Reflection/ZtReflectionUtilitiesTests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}