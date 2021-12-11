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
	                Collection = ReflectedCollection<>()
	                    .RegisterClass(ReflectedClass<ReflectionTestStruct>());
	}
	
	TEST_F(ReflectedCollectionTests, GetReflectedClassesTest)
	{
	    ReflectedCollection<std::tuple<ReflectedClass<ReflectionTestStruct>>>
	            Collection = ReflectedCollection<>()
	            .RegisterClass(ReflectedClass<ReflectionTestStruct>());
	
	    auto& Classes = Collection.GetReflectedClasses();
	}
	
	TEST_F(ReflectedCollectionTests, ComplexRegisterTest)
	{
	    [[maybe_unused]] auto Collection = ReflectedCollection()
	            .RegisterClass(ReflectedClass<ReflectionTestStruct>()
	                    .RegisterFunction(&ReflectionTestStruct::SimpleMethod)
	                    .RegisterFunction(&ReflectionTestStruct::MethodReturnSum))
	            .RegisterClass(ReflectedClass<SimpleTestStruct>()
	                    .RegisterFunction(&SimpleTestStruct::Foo)
	                    .RegisterProperty(&SimpleTestStruct::Integer));
	}

}