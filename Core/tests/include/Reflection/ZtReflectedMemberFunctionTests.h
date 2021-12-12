#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"
#include "ZtReflectionTestStruct.h"

namespace zt::tests
{

	class ReflectedMemberFunctionTests : public ::testing::Test
	{
	protected:

	};

	TEST_F(ReflectedMemberFunctionTests, CreateFromSimpleMethodTest)
	{
		ReflectedMemberFunction<void (ReflectionTestStruct::*)()> reflectedMemberFunction(&ReflectionTestStruct::simpleMethod);
	}

	TEST_F(ReflectedMemberFunctionTests, CreateFromComplexMethodTest)
	{
		ReflectedMemberFunction<int (ReflectionTestStruct::*)(const int&, const int&) const> reflectedMemberFunction(&ReflectionTestStruct::constMethodReturnSum);
	}

	TEST_F(ReflectedMemberFunctionTests, GetPointerTest)
	{
		using FunctionPointerType = void (ReflectionTestStruct::*)();

		ReflectedMemberFunction<FunctionPointerType> reflectedMemberFunction(&ReflectionTestStruct::simpleMethod);

		FunctionPointerType functionPointer = reflectedMemberFunction.getPointer();
	}

}