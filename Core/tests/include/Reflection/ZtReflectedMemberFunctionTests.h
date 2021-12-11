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
		ReflectedMemberFunction<void (ReflectionTestStruct::*)()> ReflectedMemberFunction(&ReflectionTestStruct::SimpleMethod);
	}

	TEST_F(ReflectedMemberFunctionTests, CreateFromComplexMethodTest)
	{
		ReflectedMemberFunction<int (ReflectionTestStruct::*)(const int&, const int&) const> ReflectedMemberFunction(&ReflectionTestStruct::ConstMethodReturnSum);
	}

	TEST_F(ReflectedMemberFunctionTests, GetPointerTest)
	{
		using FunctionPointerType = void (ReflectionTestStruct::*)();

		ReflectedMemberFunction<FunctionPointerType> ReflectedMemberFunction(&ReflectionTestStruct::SimpleMethod);

		FunctionPointerType FunctionPointer = ReflectedMemberFunction.GetPointer();
	}

}