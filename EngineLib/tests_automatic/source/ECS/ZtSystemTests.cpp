#pragma once

#include "Zinet/Engine/ECS/ZtSystem.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"

#include <gtest/gtest.h>

namespace zt::engine::ecs::tests
{
	class TestComponent : public Component
	{
	public:

		TestComponent(core::UniqueID&& uniqueID, core::ID entityID) : Component(std::move(uniqueID), entityID) {}

		void preUpdate(core::Time elapsedTime) override { ++preUpdateCalledCounter; }
		void update(core::Time elapsedTime) override { ++updateCalledCounter; }
		void postUpdate(core::Time elapsedTime) override { ++postUpdateCalledCounter; }

		size_t getPreUpdateCalledCounter() const { return preUpdateCalledCounter; }
		size_t getUpdateCalledCounter() const { return updateCalledCounter; }
		size_t getPostUpdateCalledCounter() const { return postUpdateCalledCounter; }

		inline static const int startValue = 10;
		int value = startValue;

	private:

		size_t preUpdateCalledCounter = 0u;
		size_t updateCalledCounter = 0u;
		size_t postUpdateCalledCounter = 0u;

	};

	class TestSystem : public System<TestComponent>
	{
	public:

		using BaseT = System<TestComponent>;

		bool initialize() override { return BaseT::initialize(); }

		void preUpdate(core::Time elapsedTime) override { BaseT::preUpdate(elapsedTime); }

		void update(core::Time elapsedTime) override { BaseT::update(elapsedTime); }

		void postUpdate(core::Time elapsedTime) override { BaseT::postUpdate(elapsedTime); }
	};

	class SystemSimpleTests : public ::testing::Test
	{
	protected:

		TestSystem system;

		static_assert(std::is_default_constructible_v<TestSystem>);
		static_assert(!std::is_copy_constructible_v<TestSystem>);
		static_assert(!std::is_copy_assignable_v<TestSystem>);
		static_assert(std::is_move_constructible_v<TestSystem>);
		static_assert(std::is_move_assignable_v<TestSystem>);
		static_assert(std::is_destructible_v<TestSystem>);
		static_assert(std::is_same_v<TestComponent, TestSystem::ComponentT>);
		static_assert(std::is_same_v<ComponentWeakRef<TestComponent>, TestSystem::ComponentWeakRefT>);
		static_assert(std::is_same_v<ComponentStrongRef<TestComponent>, TestSystem::ComponentStrongRefT>);
	};

	TEST_F(SystemSimpleTests, GetComponents)
	{
		bool result = core::TestGetters<std::vector<TestSystem::ComponentStrongRefT>, TestSystem>(&TestSystem::getComponents, &TestSystem::getComponents, system);
		ASSERT_TRUE(result); 
	}

	TEST_F(SystemSimpleTests, AddComponent)
	{
		const size_t entityUniqueIDNumber = 8u;
		core::UniqueID entityUniqueID{ entityUniqueIDNumber };
		const Entity entity{ std::move(entityUniqueID) };
		TestSystem::ComponentWeakRefT component = system.addComponent(entity);
		EXPECT_TRUE(component.isValid());

		component = system.addComponent(entity);
		EXPECT_TRUE(component.isValid());

		const auto& components = system.getComponents();
		ASSERT_EQ(components.size(), 2u);
		EXPECT_TRUE(components[0]->getUniqueID() == 0u);
		EXPECT_TRUE(components[0]->getOwnerID() == entityUniqueIDNumber);
		EXPECT_TRUE(components[1]->getUniqueID() == 1u);
		EXPECT_TRUE(components[1]->getOwnerID() == entityUniqueIDNumber);
	}

	TEST_F(SystemSimpleTests, AddComponentAfterDestroy)
	{
		const size_t entityUniqueIDNumber = 8u;
		core::UniqueID entityUniqueID{ entityUniqueIDNumber };
		const Entity entity{ std::move(entityUniqueID) };

		auto component = system.addComponent(entity);
		ASSERT_TRUE(component.isValid());

		const bool result = system.destroyComponent(component.getOwnerID());
		ASSERT_TRUE(result);

		component = system.addComponent(entity);
		ASSERT_TRUE(component.isValid());

		const auto& components = system.getComponents();
		ASSERT_EQ(components.size(), 1u);
		ASSERT_TRUE(components.front().isValid());
	}

	TEST_F(SystemSimpleTests, DestroyComponent)
	{
		const core::ID invalidID{ 5324234u };
		bool result = system.destroyComponent(invalidID);
		EXPECT_FALSE(result);

		const size_t entityUniqueIDNumber = 8u;
		core::UniqueID entityUniqueID{ entityUniqueIDNumber };
		const Entity entity{ std::move(entityUniqueID) };

		auto component = system.addComponent(entity);
		EXPECT_TRUE(component.isValid());

		result = system.destroyComponent(component.getOwnerID());
		EXPECT_TRUE(result);

		const auto& components = system.getComponents();
		ASSERT_EQ(components.size(), 1u);
		ASSERT_FALSE(components.front().isValid());
	}

	TEST_F(SystemSimpleTests, Initialize)
	{
		bool result = system.initialize();
		EXPECT_TRUE(result);
	}

	TEST_F(SystemSimpleTests, PreUpdate)
	{
		const size_t entityUniqueIDNumber = 8u;
		core::UniqueID entityUniqueID{ entityUniqueIDNumber };
		const Entity entity{ std::move(entityUniqueID) };

		auto component = system.addComponent(entity);
		ASSERT_TRUE(component.isValid());

		system.preUpdate({});
		EXPECT_EQ(component->getPreUpdateCalledCounter(), 1u);

		system.preUpdate({});
		EXPECT_EQ(component->getPreUpdateCalledCounter(), 2u);
	}

	TEST_F(SystemSimpleTests, Update)
	{
		const size_t entityUniqueIDNumber = 8u;
		core::UniqueID entityUniqueID{ entityUniqueIDNumber };
		const Entity entity{ std::move(entityUniqueID) };

		auto component = system.addComponent(entity);
		ASSERT_TRUE(component.isValid());

		system.update({});
		EXPECT_EQ(component->getUpdateCalledCounter(), 1u);

		system.update({});
		EXPECT_EQ(component->getUpdateCalledCounter(), 2u);
	}

	TEST_F(SystemSimpleTests, PostUpdate)
	{
		const size_t entityUniqueIDNumber = 8u;
		core::UniqueID entityUniqueID{ entityUniqueIDNumber };
		const Entity entity{ std::move(entityUniqueID) };

		auto component = system.addComponent(entity);
		ASSERT_TRUE(component.isValid());

		system.postUpdate({});
		EXPECT_EQ(component->getPostUpdateCalledCounter(), 1u);

		system.postUpdate({});
		EXPECT_EQ(component->getPostUpdateCalledCounter(), 2u);
	}
}
