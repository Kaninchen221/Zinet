#pragma once

#include "Zinet/Engine/ZtEngineContext.hpp"

#include "Zinet/Core/Reflection/ZtClassesInfos.hpp"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class EngineContextSimpleTests : public ::testing::Test
	{
	protected:

		EngineContext engineContext;

		static_assert(std::is_default_constructible_v<EngineContext>);
		static_assert(std::is_copy_constructible_v<EngineContext>);
		static_assert(std::is_copy_assignable_v<EngineContext>);
		static_assert(std::is_move_constructible_v<EngineContext>);
		static_assert(std::is_move_assignable_v<EngineContext>);
		static_assert(std::is_destructible_v<EngineContext>);
	};

	TEST_F(EngineContextSimpleTests, Pass)
	{
		
	}

	class EngineContextTests : public ::testing::Test
	{
	protected:

		EngineContext engineContext;

	};

	TEST_F(EngineContextTests, Pass)
	{

	}
}