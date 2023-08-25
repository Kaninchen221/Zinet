#pragma once

#include "Zinet/Reflection/ZtModule.h"
#include "Zinet/Reflection/ZtTestClass.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::reflection::tests
{
// 	class ModuleTests : public ::testing::Test
// 	{
// 	protected:
// 
// 		Module module;
// 	};
// 
// 	TEST_F(ModuleTests, ReflectClass)
// 	{
// 		std::string_view className = "TestClass";
// 		[[maybe_unused]] ReflectedClass& reflectedClass = module.reflectClass<TestClass>(className);
// 	}
// 
// 	TEST_F(ModuleTests, GetReflectedClass)
// 	{
// 		typedef ReflectedClass*(Module::* ExpectedFunction)(std::string_view);
// 		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Module::getReflectedClass));
// 
// 		std::string_view className = "TestClass";
// 		ReflectedClass* reflectedClass = module.getReflectedClass(className);
// 		EXPECT_EQ(reflectedClass, nullptr);
// 
// 		module.reflectClass<TestClass>(className);
// 
// 		reflectedClass = module.getReflectedClass(className);
// 		EXPECT_NE(reflectedClass, nullptr);
// 	}
}
