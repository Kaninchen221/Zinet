#pragma once

#include "Zinet/Core/Reflection/ZtClassPropertyInfo.hpp"

#include "ZtReflectionClassForClassInfo.hpp"

#include <gtest/gtest.h>
#include <xutility>

namespace zt::core::reflection::tests
{
	class ClassPropertiesInfosTests : public ::testing::Test
	{
	protected:

		using ClassPropertiesInfosT = ClassPropertiesInfos<1>;
		using ArrayTypeParam = std::array<ClassPropertyInfo, 3>();

		static_assert(std::is_default_constructible_v<ClassPropertiesInfosT>);
		static_assert(std::is_copy_constructible_v<ClassPropertiesInfosT>);
		static_assert(std::is_copy_assignable_v<ClassPropertiesInfosT>);
		static_assert(std::is_move_constructible_v<ClassPropertiesInfosT>);
		static_assert(std::is_move_assignable_v<ClassPropertiesInfosT>);
		static_assert(std::is_destructible_v<ClassPropertiesInfosT>);

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST(ClassPropertiesInfosTest, FromArray)
	{
		const size_t Size = 3u;
		std::array<ClassPropertyInfo, Size> arrayParam;
		auto classPropertiesInfos = ArrayToClassPropertiesInfos(arrayParam);
	}

	TEST_F(ClassPropertiesInfosTests, FindFirstWithPropertyName)
	{
		auto classPropertiesInfos = TestReflectionClassForClassInfo::ClassInfo::GetClassPropertiesInfos();
		const std::string_view expectedPropertyName = "i1";
		auto optClassPropertyInfo = classPropertiesInfos.findFirstWithPropertyName(expectedPropertyName);
		ASSERT_TRUE(optClassPropertyInfo);
		ASSERT_EQ(optClassPropertyInfo->getPropertyName(), expectedPropertyName);
	}

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
 		const size_t expectedMembersCount = 5u;
		const ClassPropertiesInfos<expectedMembersCount> classPropertiesInfos = TestReflectionClassForClassInfo::ClassInfo::GetClassPropertiesInfos();
 		ASSERT_EQ(classPropertiesInfos.get().size(), expectedMembersCount);
	}

	TEST_F(ClassPropertyInfoRealInstanceTests, GetCopyOfAllMembers)
	{
		auto copyOfAllMembers = testClass.getCopyOfAllMembers();
		EXPECT_EQ(testClass.i1, std::get<0>(copyOfAllMembers));
		EXPECT_EQ(testClass.b1, std::get<1>(copyOfAllMembers));
		EXPECT_EQ(testClass.lli1, std::get<2>(copyOfAllMembers));
		EXPECT_EQ(testClass.d1, std::get<3>(copyOfAllMembers));
		EXPECT_EQ(testClass.i2, std::get<4>(copyOfAllMembers));
	}

	TEST_F(ClassPropertyInfoRealInstanceTests, Is)
	{
		const auto members = TestReflectionClassForClassInfo::ClassInfo::GetClassPropertiesInfos();
		const auto& memberI1 = members.get().front();
		const bool isBool = memberI1.is<bool>();
		ASSERT_FALSE(isBool);

		const bool isInt = memberI1.is<int>();
		ASSERT_TRUE(isInt);
	}

	TEST_F(ClassPropertyInfoRealInstanceTests, Cast)
	{
		auto classPropertiesInfos = TestReflectionClassForClassInfo::ClassInfo::GetClassPropertiesInfos();
		auto& classPropertyInfoI1 = classPropertiesInfos.get().front();
		const bool isI1Int = classPropertyInfoI1.is<int>();
		ASSERT_TRUE(isI1Int);

		/// Test memoryOffset is equal to 0
		ASSERT_EQ(classPropertyInfoI1.getMemoryOffset(), 0u);
		int& i1 = classPropertyInfoI1.cast<int>(&testClass);
		ASSERT_EQ(&i1, &testClass.i1);
		ASSERT_EQ(i1, testClass.i1);

		auto optClassPropertyInfo = classPropertiesInfos.findFirstWithPropertyName("i2");
		if (optClassPropertyInfo)
		{
			auto& classPropertyInfoI2 = *optClassPropertyInfo;
			const bool isI2Int = classPropertyInfoI2.is<int>();
			ASSERT_TRUE(isI2Int);

			/// Test memoryOffset is greater than 0
			ASSERT_GT(classPropertyInfoI2.getMemoryOffset(), 0u);
			int& i2 = classPropertyInfoI2.cast<int>(&testClass);
			ASSERT_EQ(&i2, &testClass.i2);
			ASSERT_EQ(i2, testClass.i2);
		}
	}
}