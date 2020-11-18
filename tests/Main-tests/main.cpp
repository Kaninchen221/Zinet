
#include "gtest/gtest.h"

#include "ZtLogger-tests.h"
#include "ZtMainException-tests.h"
#include "ZtEntity-tests.h"
#include "ZtSystem-tests.h"
#include "ZtClock-tests.h"
#include "ZtTime-tests.h"
#include "ZtuniqueIndexer-tests.h"
#include "ZtIdentificator-tests.h"
#include "ZtComponentsManager-tests.h"
#include "ZtComponent-tests.h"
#include "ZtSystemsManager-tests.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}