#pragma once

#include "Zinet/Core/ZtEventBroadcaster.h"

#include <gtest/gtest.h>

namespace zt::tests
{

	class EventDispatcherTests : public ::testing::Test
	{
	protected:

		struct ObjectDerived : Object
		{
			void foo() { fooCalled = true; }

			ZINET_MAKE_FUNCTOR(ObjectDerived, foo)

				std::shared_ptr<ObjectDerived_FUNCTOR_foo> functor = std::make_shared<ObjectDerived_FUNCTOR_foo>(*this);

			bool called() { return fooCalled; }

		protected:
			bool fooCalled = false;
		};
	};

	TEST_F(EventDispatcherTests, AddTest)
	{
		EventBroadcaster eventDispatcher;
		ObjectDerived object;

		EventCallback eventCallback;
		eventCallback.functor = object.functor;
		eventDispatcher.add(eventCallback);

		eventDispatcher.broadcast();

		bool called = object.called();
		ASSERT_TRUE(called);
	}

}