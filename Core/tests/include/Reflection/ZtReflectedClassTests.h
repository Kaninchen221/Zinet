#pragma once

#include "ZtReflectionTestStruct.h"

#include "Zinet/Core/Reflection/ZtReflectedClass.h"

class ZtReflectedClassTests : public ::testing::Test
{
protected:

	ZtReflectionTestStruct TestStruct;

};

TEST_F(ZtReflectedClassTests, CreateEmptyReflectedClassTest)
{
	auto ReflectedClass = ZtReflectedClass<ZtReflectionTestStruct>();
}

TEST_F(ZtReflectedClassTests, RegisterMemberPropertiesTest)
{
	auto ReflectedClass = ZtReflectedClass<ZtReflectionTestStruct>()
		.RegisterProperty(&ZtReflectionTestStruct::IntMember)
		.RegisterProperty(&ZtReflectionTestStruct::UnsignedIntMember);
}

TEST_F(ZtReflectedClassTests, RegisterMemberFunctionsTest)
{
	auto ReflectedClass = ZtReflectedClass<ZtReflectionTestStruct>()
		.RegisterFunction(&ZtReflectionTestStruct::MethodReturnSum)
		.RegisterFunction(&ZtReflectionTestStruct::NotLiteralTypeParam);
}

TEST_F(ZtReflectedClassTests, RegisterMemberFunctionAndPropertyTest)
{
	auto ReflectedClass = ZtReflectedClass<ZtReflectionTestStruct>()
		.RegisterFunction(&ZtReflectionTestStruct::MethodReturnSum)
		.RegisterProperty(&ZtReflectionTestStruct::IntMember);
}

TEST_F(ZtReflectedClassTests, GetReflectedPropertiesTest)
{
	auto ReflectedClass = ZtReflectedClass<ZtReflectionTestStruct>()
		.RegisterProperty(&ZtReflectionTestStruct::IntMember)
		.RegisterProperty(&ZtReflectionTestStruct::UnsignedIntMember);

	auto ReflectedProperties = ReflectedClass.GetReflectedProperties();

	using ReflectedPropertiesType = decltype(ReflectedProperties);
	size_t ActualPropertiesCount = std::tuple_size<ReflectedPropertiesType>::value;
	size_t ExpectedPropertiesCount = 2u;

	ASSERT_EQ(ActualPropertiesCount, ExpectedPropertiesCount);
}

TEST_F(ZtReflectedClassTests, GetReflectedFunctionsTest)
{
    auto ReflectedClass = ZtReflectedClass<ZtReflectionTestStruct>()
            .RegisterFunction(&ZtReflectionTestStruct::MethodReturnSum)
            .RegisterFunction(&ZtReflectionTestStruct::NotLiteralTypeParam);

    auto ReflectedFunctions = ReflectedClass.GetReflectedFunctions();

    using ReflectedFunctionsType = decltype(ReflectedFunctions);
    size_t ActualFunctionsCount = std::tuple_size<ReflectedFunctionsType>::value;
    size_t ExpectedFunctionsCount = 2u;

    ASSERT_EQ(ActualFunctionsCount, ExpectedFunctionsCount);
}