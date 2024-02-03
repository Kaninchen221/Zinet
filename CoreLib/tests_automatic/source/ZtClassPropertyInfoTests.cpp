#pragma once

#include "Zinet/Core/Reflection/ZtClassPropertyInfo.hpp"

#include "ZtReflectionClassForClassInfo.hpp"

#include <gtest/gtest.h>

namespace zt::core::reflection::tests
{
	class ClassPropertyInfoTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<ClassPropertyInfo>);
		static_assert(std::is_constructible_v<ClassPropertyInfo, std::int64_t, std::string_view, std::string_view>);
		static_assert(std::is_copy_constructible_v<ClassPropertyInfo>);
		static_assert(std::is_copy_assignable_v<ClassPropertyInfo>);
		static_assert(std::is_move_constructible_v<ClassPropertyInfo>);
		static_assert(std::is_move_assignable_v<ClassPropertyInfo>);
		static_assert(std::is_destructible_v<ClassPropertyInfo>);

		const size_t memoryOffset = 24;
		const std::string_view propertyName = "TestName";
		const std::string_view propertyTypeName = "TestPropertyTypeName";
		ClassPropertyInfo classPropertyInfo{ memoryOffset, propertyName, propertyTypeName };

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(ClassPropertyInfoTests, Offset)
	{
		size_t actualOffset = classPropertyInfo.getMemoryOffset();
		EXPECT_EQ(actualOffset, memoryOffset);
	}

	TEST_F(ClassPropertyInfoTests, PropertyName)
	{
		std::string_view actualPropertyName = classPropertyInfo.getPropertyName();
		EXPECT_EQ(actualPropertyName, propertyName);
	}

	TEST_F(ClassPropertyInfoTests, PropertyTypeName)
	{
		std::string_view actualPropertyTypeName = classPropertyInfo.getPropertyTypeName();
		EXPECT_EQ(actualPropertyTypeName, propertyTypeName);
	}

	class ClassPropertyInfoRealInstanceTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<ClassPropertyInfo>);
		static_assert(std::is_constructible_v<ClassPropertyInfo, std::int64_t, std::string_view, std::string_view>);
		static_assert(std::is_copy_constructible_v<ClassPropertyInfo>);
		static_assert(std::is_copy_assignable_v<ClassPropertyInfo>);
		static_assert(std::is_move_constructible_v<ClassPropertyInfo>);
		static_assert(std::is_move_assignable_v<ClassPropertyInfo>);
		static_assert(std::is_destructible_v<ClassPropertyInfo>);

		TestReflectionClassForClassInfo testClass;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST(ClassPropertyInfoRealInstanceTest, GetClassPropertiesInfos)
	{
		const auto members = TestReflectionClassForClassInfo::ClassInfo::GetClassPropertiesInfos();
 		const size_t expectedMembersCount = 4u;
 		ASSERT_EQ(members.size(), expectedMembersCount);
	}

	TEST_F(ClassPropertyInfoRealInstanceTests, GetCopyOfAllMembers)
	{
		auto copyOfAllMembers = testClass.getCopyOfAllMembers();
		EXPECT_EQ(testClass.i1, std::get<0>(copyOfAllMembers));
		EXPECT_EQ(testClass.b1, std::get<1>(copyOfAllMembers));
		EXPECT_EQ(testClass.d1, std::get<2>(copyOfAllMembers));
		EXPECT_EQ(testClass.i2, std::get<3>(copyOfAllMembers));
	}

	TEST_F(ClassPropertyInfoRealInstanceTests, Is)
	{
		const auto members = TestReflectionClassForClassInfo::ClassInfo::GetClassPropertiesInfos();
		const auto& memberI1 = members.front();
		const bool isBool = memberI1.is<bool>();
		ASSERT_FALSE(isBool);

		const bool isInt = memberI1.is<int>();
		ASSERT_TRUE(isInt);
	}

	TEST_F(ClassPropertyInfoRealInstanceTests, Cast)
	{
		auto members = TestReflectionClassForClassInfo::ClassInfo::GetClassPropertiesInfos();
		auto& memberI1 = members.front();
		const bool isI1Int = memberI1.is<int>();
		ASSERT_TRUE(isI1Int);

		/// Test memoryOffset is equal to 0
		ASSERT_EQ(memberI1.getMemoryOffset(), 0u);
		int& i1 = memberI1.cast<int>(&testClass);
		ASSERT_EQ(&i1, &testClass.i1);
		ASSERT_EQ(i1, testClass.i1);

		auto& memberI2 = members[3];
		const bool isI2Int = memberI2.is<int>();
		ASSERT_TRUE(isI2Int);

		/// Test memoryOffset is greater than 0
		ASSERT_GT(memberI2.getMemoryOffset(), 0u);
		int& i2 = memberI2.cast<int>(&testClass);
		ASSERT_EQ(&i2, &testClass.i2);
		ASSERT_EQ(i2, testClass.i2);
	}
}