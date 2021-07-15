#pragma once

#include "Zinet/Core/ZtEventBroadcaster.h"

#include "gtest/gtest.h"

class ZtEventDispatcherTests : public ::testing::Test
{
protected:

	struct ZtObjectDerived : ZtObject
	{
		void Foo() { FooCalled = true; }

		ZINET_MAKE_FUNCTOR(ZtObjectDerived, Foo)

		std::shared_ptr<ZtObjectDerived_FUNCTOR_Foo> Functor = std::make_shared<ZtObjectDerived_FUNCTOR_Foo>(*this);

		bool Called() { return FooCalled; }

	protected:
		bool FooCalled = false;
	};
};

TEST_F(ZtEventDispatcherTests, AddTest)
{
	ZtEventBroadcaster EventDispatcher;
	ZtObjectDerived Object;
	
	ZtEventCallback EventCallback;
	EventCallback.Functor = Object.Functor;
	EventDispatcher.Add(EventCallback);

	EventDispatcher.Broadcast();

	bool Called = Object.Called();
	ASSERT_TRUE(Called);
}