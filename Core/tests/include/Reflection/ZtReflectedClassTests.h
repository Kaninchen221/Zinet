#pragma once

#include "ZtReflectionTestStruct.h"

#include "Zinet/Core/Reflection/ZtReflectedClass.h"

namespace zt::tests
{

	class ReflectedClassTests : public ::testing::Test
	{
	protected:

		ReflectionTestStruct TestStruct;

	};

	TEST_F(ReflectedClassTests, CreateEmptyReflectedClassTest)
	{
		auto Class = ReflectedClass<ReflectionTestStruct>();
	}

	TEST_F(ReflectedClassTests, RegisterMemberPropertiesTest)
	{
		auto Class = ReflectedClass<ReflectionTestStruct>();
			//.RegisterProperty(&ReflectionTestStruct::IntMember);
			//.RegisterProperty(&ReflectionTestStruct::UnsignedIntMember);

		//auto Class2 = Class.RegisterProperty(&ReflectionTestStruct::IntMember);
	}

	//TEST_F(ReflectedClassTests, RegisterMemberFunctionsTest)
	//{
	//	auto Class = ReflectedClass<ReflectionTestStruct>()
	//		.RegisterFunction(&ReflectionTestStruct::MethodReturnSum)
	//		.RegisterFunction(&ReflectionTestStruct::NotLiteralTypeParam);
	//}
	//
	//TEST_F(ReflectedClassTests, RegisterMemberFunctionAndPropertyTest)
	//{
	//	auto Class = ReflectedClass<ReflectionTestStruct>()
	//		.RegisterFunction(&ReflectionTestStruct::MethodReturnSum)
	//		.RegisterProperty(&ReflectionTestStruct::IntMember);
	//}
	//
	//TEST_F(ReflectedClassTests, GetReflectedPropertiesTest)
	//{
	//	auto Class = ReflectedClass<ReflectionTestStruct>()
	//		.RegisterProperty(&ReflectionTestStruct::IntMember)
	//		.RegisterProperty(&ReflectionTestStruct::UnsignedIntMember);
	//
	//	auto Properties = ReflectedClass.GetReflectedProperties();
	//
	//	using PropertiesType = decltype(Properties);
	//	size_t ActualPropertiesCount = std::tuple_size<ReflectedPropertiesType>::value;
	//	size_t ExpectedPropertiesCount = 2u;
	//
	//	ASSERT_EQ(ActualPropertiesCount, ExpectedPropertiesCount);
	//}
	//
	//TEST_F(ReflectedClassTests, GetReflectedFunctionsTest)
	//{
	//	auto Class = ReflectedClass<ReflectionTestStruct>()
	//		.RegisterFunction(&ReflectionTestStruct::MethodReturnSum)
	//		.RegisterFunction(&ReflectionTestStruct::NotLiteralTypeParam);
	//
	//	auto Functions = Class.GetReflectedFunctions();
	//
	//	using FunctionsType = decltype(Functions);
	//	size_t ActualFunctionsCount = std::tuple_size<ReflectedFunctionsType>::value;
	//	size_t ExpectedFunctionsCount = 2u;
	//
	//	ASSERT_EQ(ActualFunctionsCount, ExpectedFunctionsCount);
	//}
	//
	//TEST_F(ReflectedClassTests, ReflectInsideStaticAssertTest)
	//{
	//	static_assert(ReflectedClass<ReflectionTestStruct>()
	//		.RegisterFunction(&ReflectionTestStruct::MethodReturnSum)
	//		.RegisterProperty(&ReflectionTestStruct::IntMember),
	//		"ReflectedClass must be convertible to bool");
	//}

}