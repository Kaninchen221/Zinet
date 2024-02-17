#pragma once

#include "Zinet/Core/Reflection/ZtClassInfos.hpp"

#include <gtest/gtest.h>

namespace zt::core::reflection::tests
{
	class ClassInfosSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<ClassInfos>);
		static_assert(std::is_copy_constructible_v<ClassInfos>);
		static_assert(std::is_copy_assignable_v<ClassInfos>);
		static_assert(std::is_move_constructible_v<ClassInfos>);
		static_assert(std::is_move_assignable_v<ClassInfos>);
		static_assert(std::is_destructible_v<ClassInfos>);

		ClassInfos classInfos;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(ClassInfosSimpleTests, AddClassInfo)
	{
		ClassInfo classInfo;
		classInfos.addClassInfo<ClassInfo>();
	}

	TEST_F(ClassInfosSimpleTests, GetByClassNameInvalidResult)
	{
		const std::string_view className = ".00InvalidClassName";
		auto result = classInfos.getByClassName(className);
		ASSERT_FALSE(result);
	}

	TEST_F(ClassInfosSimpleTests, GetByClassNameValidResult)
	{
		classInfos.addClassInfo<ClassInfo>();
		const std::string_view className = ClassInfo().getClassName();
		auto result = classInfos.getByClassName(className);
		ASSERT_TRUE(result);
		ASSERT_EQ(result->getClassName(), className);
	}
}