#pragma once

/// Won't get breakpoint in test
#undef ZT_ALWAYS_BREAK
#define ZT_ALWAYS_BREAK

#include "Zinet/Core/ZtPointer.h"
#include "Zinet/Core/ZtObject.h"
#include "gtest/gtest.h"

class ZtPointerTests : public ::testing::Test
{
protected:

	class ZtObjectChild : public ZtObject
	{};

	class ZtObjectChildWithParams : public ZtObject
	{
	public:
		ZtObjectChildWithParams(int Number, std::string String) 
			: Number(Number), String(String) {};

		int Number;
		std::string String;
	};

	using PointerType = ZtPointer<ZtObjectChild>;
	using PointerTypeWithParams = ZtPointer<ZtObjectChildWithParams>;
};

TEST_F(ZtPointerTests, CreateEmptyTest)
{
	[[maybe_unused]] PointerType Pointer;
}

TEST_F(ZtPointerTests, IsNullTest)
{
	PointerType Pointer;

	bool IsNull = Pointer.IsNull();
	ASSERT_TRUE(IsNull);
}

TEST_F(ZtPointerTests, CreateTest)
{
	PointerType Pointer = PointerType::Create();

	bool IsNull = Pointer.IsNull();
	ASSERT_FALSE(IsNull);
}

TEST_F(ZtPointerTests, ArrowOperatorInvalidTest)
{
	PointerType Pointer;
	ZtObjectChild* Object = Pointer.operator->();

	bool IsNull = Object == nullptr;
	ASSERT_TRUE(IsNull);
}

TEST_F(ZtPointerTests, ArrowOperatorValidTest)
{
	PointerType Pointer = PointerType::Create();
	ZtObjectChild* Object = Pointer.operator->();
	
	bool IsNull = Object == nullptr;
	ASSERT_FALSE(IsNull);
}

TEST_F(ZtPointerTests, MoveTest)
{
	PointerType Pointer1 = PointerType::Create();
	PointerType Pointer2;

	Pointer2 = std::move(Pointer1);

	bool IsPointer1Null = Pointer1.IsNull();
	ASSERT_TRUE(IsPointer1Null);

	bool IsPointer2Null = Pointer2.IsNull();
	ASSERT_FALSE(IsPointer2Null);
}

TEST_F(ZtPointerTests, AssignTest)
{
	PointerType Pointer1 = PointerType::Create();
	PointerType Pointer2;

	Pointer2 = Pointer1;

	bool IsPointer1Null = Pointer1.IsNull();
	ASSERT_TRUE(IsPointer1Null);

	bool IsPointer2Null = Pointer2.IsNull();
	ASSERT_FALSE(IsPointer2Null);
}

TEST_F(ZtPointerTests, OperatorBoolTest)
{
	PointerType Pointer;
	ASSERT_FALSE(Pointer);

	Pointer = PointerType::Create();
	ASSERT_TRUE(Pointer);
}

TEST_F(ZtPointerTests, CastToTest)
{
	PointerType Pointer = PointerType::Create();
	ZtPointer<ZtObject> Casted = Pointer.CastTo<ZtObject>();

	ASSERT_FALSE(Pointer);
	ASSERT_TRUE(Casted);
}

TEST_F(ZtPointerTests, CreateWithParams)
{
	int ExpectedNumber = 300;
	std::string ExpectedString = "string";
	PointerTypeWithParams Pointer = PointerTypeWithParams::Create(ExpectedNumber, ExpectedString);

	int ActualNumber = Pointer->Number;
	std::string ActualString = Pointer->String;
}