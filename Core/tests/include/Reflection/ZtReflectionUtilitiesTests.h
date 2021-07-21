#pragma once

#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

class ZtReflectionUtilitiesTests : public ::testing::Test
{
protected:

	using TestZtConcatTwoEmptyTupleTypes = ZtConcatTwoTupleTypes<std::tuple<>, std::tuple<>>;

	using TestZtMakePropertyTuple = ZtMakePropertyTuple<int ZtReflectionUtilitiesTests::*>;

	using TestZtMakeFunctionTuple = ZtMakeFunctionTuple<int ZtReflectionUtilitiesTests::*>;

};

TEST_F(ZtReflectionUtilitiesTests, TupleApplyTest)
{
    auto ActualTuple = std::make_tuple<int, double, int>( 5, 2, 8 );
    auto Callable = [](auto& Element) { Element += 2; };
    ZtApplyToTuple(ActualTuple, Callable);

    auto ExpectedTuple = std::make_tuple( 7, 4, 10 );
    ASSERT_EQ(ActualTuple, ExpectedTuple);
}