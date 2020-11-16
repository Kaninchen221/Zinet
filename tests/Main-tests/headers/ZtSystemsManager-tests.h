#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ECRS/ZtSystem.h"
#include "Zinet/Main/ECRS/ZtSystemsManager.h"

class ZtSystemsManagerTests : public ::testing::Test {
protected:

	class SystemDummy_1 : public zt::System<zt::Component> {
	public:
		void update(ComponentsContainer& components, zt::Time::Microseconds elapsedTime) override {}
	};

	class SystemDummy_2 : public zt::System<zt::Component> {
	public:
		void update(ComponentsContainer& components, zt::Time::Microseconds elapsedTime) override {}
	};

	using SystemsManager = zt::SystemManager<SystemDummy_1, SystemDummy_2>;

};

TEST_F(ZtSystemsManagerTests, activeTest) {

	using System = SystemDummy_1;

	SystemsManager manager;
	manager.active<System>();

	bool isActive = manager.isActive<System>();

	ASSERT_TRUE(isActive);
}

TEST_F(ZtSystemsManagerTests, deactivateTest) {

	using System = SystemDummy_1;
	SystemsManager manager;
	manager.active<System>();
	manager.deactivate<System>();

}

TEST_F(ZtSystemsManagerTests, updateTest) {

	using System = SystemDummy_1;
	using ComponentsContainer = zt::System<zt::Component>::ComponentsContainer;

	ComponentsContainer components;
	zt::Time::Microseconds elapsedTime{};
	SystemsManager manager;
	manager.active<System>();

	manager.update<System>(components, elapsedTime);
}

TEST_F(ZtSystemsManagerTests, updateThrowTest) {

	using System = SystemDummy_1;
	using ComponentsContainer = zt::System<zt::Component>::ComponentsContainer;

	ComponentsContainer components;
	zt::Time::Microseconds elapsedTime{};
	SystemsManager manager;

	ASSERT_THROW(manager.update<System>(components, elapsedTime), zt::MainException);
}

