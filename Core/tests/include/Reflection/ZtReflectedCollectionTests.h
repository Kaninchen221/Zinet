#pragma once

#include "Zinet/Core/Reflection/ZtReflectedCollection.h"

class ZtReflectedCollectionTests : public ::testing::Test
{
protected:



};

TEST_F(ZtReflectedCollectionTests, SimpleRegisterTest)
{
    [[maybe_unused]] ZtReflectedCollection<std::tuple<ZtReflectedClass<ZtReflectionTestStruct>>>
                ReflectedCollection = ZtReflectedCollection<>()
                    .RegisterClass(ZtReflectedClass<ZtReflectionTestStruct>());
}

TEST_F(ZtReflectedCollectionTests, GetReflectedClassesTest)
{
    ZtReflectedCollection<std::tuple<ZtReflectedClass<ZtReflectionTestStruct>>>
            ReflectedCollection = ZtReflectedCollection<>()
            .RegisterClass(ZtReflectedClass<ZtReflectionTestStruct>());

    auto& ReflectedClasses = ReflectedCollection.GetReflectedClasses();
}

TEST_F(ZtReflectedCollectionTests, ComplexRegisterTest)
{
    [[maybe_unused]] auto ReflectedCollection = ZtReflectedCollection()
            .RegisterClass(ZtReflectedClass<ZtReflectionTestStruct>()
                    .RegisterFunction(&ZtReflectionTestStruct::SimpleMethod)
                    .RegisterFunction(&ZtReflectionTestStruct::MethodReturnSum))
            .RegisterClass(ZtReflectedClass<ZtSimpleTestStruct>()
                    .RegisterFunction(&ZtSimpleTestStruct::Foo)
                    .RegisterProperty(&ZtSimpleTestStruct::Integer));
}