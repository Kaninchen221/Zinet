#pragma once

#include "Zinet/Core/Reflection/ZtClassInfo.hpp"

#include <gtest/gtest.h>

namespace zt::core::reflection::tests
{
	class ClassInfoChildClass : public ClassInfo
	{
	public:

		std::string_view getClassName() const override { return "ClassInfoChildClass"; }

	};

	class ClassInfoSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<ClassInfo>);
		static_assert(std::is_copy_constructible_v<ClassInfo>);
		static_assert(std::is_copy_assignable_v<ClassInfo>);
		static_assert(std::is_move_constructible_v<ClassInfo>);
		static_assert(std::is_move_assignable_v<ClassInfo>);
		static_assert(std::is_destructible_v<ClassInfo>);

		ClassInfo classInfo;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(ClassInfoSimpleTests, getClassName)
	{
		auto className = classInfo.getClassName();
		EXPECT_EQ(className, "ClassInfo");
	}
}