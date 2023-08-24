#pragma once

#include "Zinet/Reflection/ZtReflectedClass.h"
#include "Zinet/Reflection/ZtTestClass.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::reflection::tests
{

	class ReflectedClassTests : public ::testing::Test
	{
	protected:

		std::string_view className = "className";
		ReflectedClass<> reflectedClass{ className };
	};

	TEST_F(ReflectedClassTests, GetName)
	{
		typedef std::string_view(ReflectedClass<>::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&ReflectedClass<>::getName));

		std::string_view actualName = reflectedClass.getName();
		EXPECT_EQ(actualName, className);
	}

	TEST_F(ReflectedClassTests, Function)
	{
		typedef int(TestClass::* SumFunction)(int, int) const;
		static_assert(zt::core::IsFunctionEqual<SumFunction>(&TestClass::sum));

		std::string_view sumName = "sum";
		ReflectedClass<std::tuple<SumFunction>> classAfterSumReflect = reflectedClass.function(&TestClass::sum, sumName);

		typedef void(TestClass::* PrintIntFunction)(int);
		static_assert(zt::core::IsFunctionEqual<PrintIntFunction>(&TestClass::printInt));

		std::string_view printIntName = "Print Int";
		ReflectedClass<std::tuple<SumFunction, PrintIntFunction>> classAfterPrintIntReflect = classAfterSumReflect.function(&TestClass::printInt, printIntName);
	}
}
