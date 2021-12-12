#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "ZtReflectionTestStruct.h"

namespace zt::tests
{

	class ReflectedMemberPropertyTests : public ::testing::Test
	{
	protected:

		ReflectedMemberPropertyTests()
			: floatReflectedMemberProperty(&ReflectionTestStruct::floatMember)
		{}

		ReflectionTestStruct classObject;
		ReflectedMemberProperty<float ReflectionTestStruct::*> floatReflectedMemberProperty;
	};

	TEST_F(ReflectedMemberPropertyTests, GetPointerTest)
	{
		float ReflectionTestStruct::* pointer = floatReflectedMemberProperty.getPointer();
	}

}