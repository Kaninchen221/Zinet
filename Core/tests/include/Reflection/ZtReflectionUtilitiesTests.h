#pragma once

#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

class ZtReflectionUtilitiesTests : public ::testing::Test
{
protected:

	using TestZtConcatTwoEmptyTupleTypes = ZtConcatTwoTupleTypes<std::tuple<>, std::tuple<>>;

	using TestZtMakePropertyTuple = ZtMakePropertyTuple<int ZtReflectionUtilitiesTests::*>;

	using TestZtMakeFunctionTuple = ZtMakeFunctionTuple<int ZtReflectionUtilitiesTests::*>;

};