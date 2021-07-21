#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "ZtReflectionTestStruct.h"

class ZtReflectedMemberPropertyTests : public ::testing::Test
{
protected:

	ZtReflectedMemberPropertyTests()
		: FloatReflectedMemberProperty(&ZtReflectionTestStruct::FloatMember)
	{}

	ZtReflectionTestStruct ClassObject;
	ZtReflectedMemberProperty<float ZtReflectionTestStruct::*> FloatReflectedMemberProperty;
};

TEST_F(ZtReflectedMemberPropertyTests, GetPointerTest)
{
	float ZtReflectionTestStruct::* Pointer = FloatReflectedMemberProperty.GetPointer();
}