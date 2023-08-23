#pragma once

#include "Zinet/Reflection/ZtReflectedClass.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::reflection::tests
{

	class ReflectedClassTests : public ::testing::Test
	{
	protected:

		std::string_view className = "className";
		ReflectedClass reflectedClass{ className };
	};

	TEST_F(ReflectedClassTests, GetName)
	{
		typedef std::string_view(ReflectedClass::*ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&ReflectedClass::getName));

		std::string_view actualName = reflectedClass.getName();
		EXPECT_EQ(actualName, className);
	}

	TEST_F(ReflectedClassTests, Function)
	{
		std::string_view name = "";

	}
}
