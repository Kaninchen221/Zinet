#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"
#include "ZtReflectionTestStruct.h"

class ZtReflectedMemberFunctionTests : public ::testing::Test
{
protected:

};

TEST_F(ZtReflectedMemberFunctionTests, InvokeConstMethodTest)
{
	using ReturnType = int;
	using ClassType = ZtReflectionTestStruct;
	constexpr int IsConst = true;

	ZtReflectedMemberFunction<ReturnType, ClassType, IsConst, const int&, const int&> ReflectedMemberFunction;
	ReflectedMemberFunction.Register(&ZtReflectionTestStruct::ConstMethodReturnSum);

	int First = 3;
	int Second = 7;
	int ExpectedSum = First + Second;

	const ClassType Object;
	ReturnType ActualSum = ReflectedMemberFunction.Invoke(Object, First, Second);
	ASSERT_EQ(ActualSum, ExpectedSum);
}

TEST_F(ZtReflectedMemberFunctionTests, InvokeMethodTest)
{
	using ReturnType = int;
	using ClassType = ZtReflectionTestStruct;
	constexpr int IsConst = false;

	ZtReflectedMemberFunction<ReturnType, ClassType, IsConst, const int&, const int&> ReflectedMemberFunction;
	ReflectedMemberFunction.Register(&ZtReflectionTestStruct::MethodReturnSum);

	int First = 3;
	int Second = 7;
	int ExpectedSum = First + Second;
	
	ClassType Object;
	ReturnType ActualSum = ReflectedMemberFunction.Invoke(Object, First, Second);
	ASSERT_EQ(ActualSum, ExpectedSum);
}