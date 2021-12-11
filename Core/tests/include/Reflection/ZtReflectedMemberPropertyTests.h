#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "ZtReflectionTestStruct.h"

namespace zt::tests
{

	class ReflectedMemberPropertyTests : public ::testing::Test
	{
	protected:

		ReflectedMemberPropertyTests()
			: FloatReflectedMemberProperty(&ReflectionTestStruct::FloatMember)
		{}

		ReflectionTestStruct ClassObject;
		ReflectedMemberProperty<float ReflectionTestStruct::*> FloatReflectedMemberProperty;
	};

	TEST_F(ReflectedMemberPropertyTests, GetPointerTest)
	{
		float ReflectionTestStruct::* Pointer = FloatReflectedMemberProperty.GetPointer();
	}

}