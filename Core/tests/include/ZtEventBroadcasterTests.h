#pragma once

#include "Zinet/Core/ZtEventBroadcaster.h"

#include "gtest/gtest.h"

namespace zt::tests
{

	class EventDispatcherTests : public ::testing::Test
	{
	protected:

		struct ObjectDerived : Object
		{
			void Foo() { FooCalled = true; }

			ZINET_MAKE_FUNCTOR(ObjectDerived, Foo)

				std::shared_ptr<ObjectDerived_FUNCTOR_Foo> Functor = std::make_shared<ObjectDerived_FUNCTOR_Foo>(*this);

			bool Called() { return FooCalled; }

		protected:
			bool FooCalled = false;
		};
	};

	TEST_F(EventDispatcherTests, AddTest)
	{
		EventBroadcaster EventDispatcher;
		ObjectDerived Object;

		EventCallback EventCallback;
		EventCallback.Functor = Object.Functor;
		EventDispatcher.Add(EventCallback);

		EventDispatcher.Broadcast();

		bool Called = Object.Called();
		ASSERT_TRUE(Called);
	}

}