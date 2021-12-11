#pragma once

#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

namespace zt::tests
{

    class ReflectionUtilitiesTests : public ::testing::Test
    {
    protected:

        using TestZtConcatTwoEmptyTupleTypes = ConcatTwoTupleTypes<std::tuple<>, std::tuple<>>;

        using TestZtMakePropertyTuple = MakePropertyTuple<int ReflectionUtilitiesTests::*>;

        using TestZtMakeFunctionTuple = MakeFunctionTuple<int ReflectionUtilitiesTests::*>;

    };

    TEST_F(ReflectionUtilitiesTests, TupleApplyTest)
    {
        auto ActualTuple = std::make_tuple<int, double, int>(5, 2, 8);
        auto Callable = [](auto& Element) { Element += 2; };
        ApplyToTuple(ActualTuple, Callable);

        auto ExpectedTuple = std::make_tuple(7, 4, 10);
        ASSERT_EQ(ActualTuple, ExpectedTuple);
    }

}