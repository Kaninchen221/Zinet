#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"
#include "ZtReflectionTestStruct.h"

class ZtReflectedMemberFunctionTests : public ::testing::Test
{
protected:

};

TEST_F(ZtReflectedMemberFunctionTests, CreateFromSimpleMethodTest)
{
	ZtReflectedMemberFunction<void (ZtReflectionTestStruct::*)()> ReflectedMemberFunction(&ZtReflectionTestStruct::SimpleMethod);
}

TEST_F(ZtReflectedMemberFunctionTests, CreateFromComplexMethodTest)
{
	ZtReflectedMemberFunction<int (ZtReflectionTestStruct::*)(const int&, const int&) const> ReflectedMemberFunction(&ZtReflectionTestStruct::ConstMethodReturnSum);
}

TEST_F(ZtReflectedMemberFunctionTests, GetPointerTest)
{
	using FunctionPointerType = void (ZtReflectionTestStruct::*)();

	ZtReflectedMemberFunction<FunctionPointerType> ReflectedMemberFunction(&ZtReflectionTestStruct::SimpleMethod);

	FunctionPointerType FunctionPointer = ReflectedMemberFunction.GetPointer();
}