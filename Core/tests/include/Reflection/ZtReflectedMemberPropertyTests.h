#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "ZtReflectionTestStruct.h"

class ZtReflectedMemberPropertyTests : public ::testing::Test
{
protected:

	ZtReflectedMemberPropertyTests()
		: IntReflectedMemberProperty(ClassObject, ClassObject.IntMember),
		FloatReflectedMemberProperty(ClassObject, ClassObject.FloatMember),
		UnsignedIntReflectedMemberProperty(ClassObject, ClassObject.UnsignedIntMember)
	{}

	ZtReflectionTestStruct ClassObject;
	ZtReflectedMemberProperty<ZtReflectionTestStruct, int> IntReflectedMemberProperty;
	ZtReflectedMemberProperty<ZtReflectionTestStruct, float> FloatReflectedMemberProperty;
	ZtReflectedMemberProperty<ZtReflectionTestStruct, unsigned int> UnsignedIntReflectedMemberProperty;
};

TEST_F(ZtReflectedMemberPropertyTests, GetInternalOffsetTest)
{
	std::int64_t ActualInternalOffset = FloatReflectedMemberProperty.GetInternalOffset();
	std::int64_t ExpectedInternalOffset = 4;

	ASSERT_EQ(ActualInternalOffset, ExpectedInternalOffset);
}

TEST_F(ZtReflectedMemberPropertyTests, GetAsPointerTest)
{
	ZtReflectionTestStruct ClassObject;
	float* ActualPointer = FloatReflectedMemberProperty.GetAsPointer(ClassObject);
	float* ExpectedPointer = &ClassObject.FloatMember;

	ASSERT_EQ(ActualPointer, ExpectedPointer);
}

TEST_F(ZtReflectedMemberPropertyTests, GetPointerTest)
{
	float ActualValue = FloatReflectedMemberProperty.GetAsValue(ClassObject);
	float ExpectedValue = ClassObject.FloatMember;

	ASSERT_EQ(ActualValue, ExpectedValue);
}