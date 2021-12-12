#pragma once

#include "Zinet/Core/Reflection/ZtReflectedCollection.h"

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
	
	    auto& classes = collection.getReflectedClasses();
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