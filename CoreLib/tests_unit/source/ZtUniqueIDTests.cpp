#pragma once

#include "Zinet/Core/ZtUniqueID.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::core::tests
{

	class UniqueIDSimpleTests : public ::testing::Test
	{
	protected:

		UniqueID uniqueID;

		static_assert(std::is_default_constructible_v<UniqueID>);
		static_assert(std::is_constructible_v<UniqueID, size_t>);
		static_assert(!std::is_copy_constructible_v<UniqueID>);
		static_assert(!std::is_copy_assignable_v<UniqueID>);
		static_assert(std::is_move_constructible_v<UniqueID>);
		static_assert(std::is_move_assignable_v<UniqueID>);
		static_assert(std::is_destructible_v<UniqueID>);
		
		static_assert(UniqueID::InvalidID == std::numeric_limits<size_t>::max());
	};

	TEST_F(UniqueIDSimpleTests, GetNumber)
	{
		size_t actual = uniqueID.getNumber();
		size_t expected = UniqueID::InvalidID;
		EXPECT_EQ(actual, expected);

		expected = 5u;
		uniqueID = UniqueID{ expected };
		actual = uniqueID.getNumber();
		EXPECT_EQ(actual, expected);
	}

	TEST_F(UniqueIDSimpleTests, MoveConstructible)
	{
		const size_t expected = 1033u;
		uniqueID = UniqueID{ expected };
		UniqueID other{ std::move(uniqueID) };

		EXPECT_EQ(other.getNumber(), expected);
		EXPECT_EQ(uniqueID.getNumber(), UniqueID::InvalidID);
	}

	TEST_F(UniqueIDSimpleTests, MoveAssignable)
	{
		const size_t expected = 1033u;
		uniqueID = UniqueID{ expected };
		UniqueID other = std::move(uniqueID);

		EXPECT_EQ(other.getNumber(), expected);
		EXPECT_EQ(uniqueID.getNumber(), UniqueID::InvalidID);
	}

	TEST_F(UniqueIDSimpleTests, CompareWithNumber)
	{
		EXPECT_FALSE(uniqueID == 5u);
		EXPECT_TRUE(uniqueID == UniqueID::InvalidID);
	}

	class UniqueIDTests : public ::testing::Test
	{
	protected:

		UniqueID uniqueID;

	};

	TEST_F(UniqueIDTests, Pass)
	{

	}
}
