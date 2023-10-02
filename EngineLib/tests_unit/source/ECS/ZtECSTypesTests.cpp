#pragma once

#include "Zinet/Engine/ECS/ZtECSTypes.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::engine::ecs::tests
{

	class ECSTypesTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_same_v<ecs::Types::EntityID, size_t>);

	};

	TEST_F(ECSTypesTests, pass)
	{

	}
}
