#pragma once

#include "Zinet/Core/Reflection/ZtReflectedCollection.h"
#include "Zinet/Core/Reflection/ZtReflectedClass.h"

#include "ZtReflectionTestStruct.cpp"

#include <gtest/gtest.h>

#include <tuple>

namespace zt::tests
{

	class ReflectedCollectionTests : public ::testing::Test
	{
	protected:



	};

	TEST_F(ReflectedCollectionTests, SimpleRegisterTest)
	{
	    [[maybe_unused]] ReflectedCollection<std::tuple<ReflectedClass<ReflectionTestStruct>>>
	                collection = ReflectedCollection<>()
	                    .registerClass(ReflectedClass<ReflectionTestStruct>());
	}
	
	TEST_F(ReflectedCollectionTests, GetReflectedClassesTest)
	{
	    ReflectedCollection<std::tuple<ReflectedClass<ReflectionTestStruct>>>
	            collection = ReflectedCollection<>()
	            .registerClass(ReflectedClass<ReflectionTestStruct>());
	
		[[maybe_unused]] auto& classes = collection.getReflectedClasses();
	}
	
	TEST_F(ReflectedCollectionTests, ComplexRegisterTest)
	{
	    [[maybe_unused]] auto collection = ReflectedCollection()
	            .registerClass(ReflectedClass<ReflectionTestStruct>()
	                    .registerFunction(&ReflectionTestStruct::simpleMethod)
	                    .registerFunction(&ReflectionTestStruct::methodReturnSum))
	            .registerClass(ReflectedClass<SimpleTestStruct>()
	                    .registerFunction(&SimpleTestStruct::foo)
	                    .registerProperty(&SimpleTestStruct::integer));
	}

}