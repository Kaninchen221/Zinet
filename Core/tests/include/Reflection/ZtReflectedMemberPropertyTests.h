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
		[[maybe_unused]] float ReflectionTestStruct::* pointer = floatReflectedMemberProperty.getPointer();
	}

}