#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ECRS/ZtComponentsManager.h"
#include "Zinet/Main/ECRS/ZtComponent.h"

class ZtComponentsManagerTests : public ::testing::Test {
protected:

	struct Dummy_1 : public zt::Component { Dummy_1(zt::Identificator identificator) noexcept : Component(identificator) {} };
	struct Dummy_2 : public zt::Component { Dummy_2(zt::Identificator identificator) noexcept : Component(identificator) {} };
	struct Dummy_3 : public zt::Component { Dummy_3(zt::Identificator identificator) noexcept : Component(identificator) {} };

	using ComponentsManager = zt::ComponentsManager<Dummy_1, Dummy_2, Dummy_3>;

	ComponentsManager componentsManager;

	ZtComponentsManagerTests() {

	}

	template<class ComponentDerivedType>
	void feedComponentsManager(zt::Identificator id, size_t componentsCount) {

		for (auto i = 0u; i < componentsCount; ++i) {
			componentsManager.createComponent<ComponentDerivedType>(id);
		}

	}

};

TEST_F(ZtComponentsManagerTests, createTest) {

	auto expectedDummy_1Count = 2u;
	auto expectedDummy_2Count = 1u;
	auto expectedDummy_3Count = 10u;
	auto id = zt::Identificator(34u);

	feedComponentsManager<Dummy_1>(id, expectedDummy_1Count);
	feedComponentsManager<Dummy_2>(id, expectedDummy_2Count);
	feedComponentsManager<Dummy_3>(id, expectedDummy_3Count);

	auto dummy_1Components = componentsManager.getComponentsByType<Dummy_1>();
	auto dummy_2Components = componentsManager.getComponentsByType<Dummy_2>();
	auto dummy_3Components = componentsManager.getComponentsByType<Dummy_3>();

	auto dummy_1ComponentsCount = dummy_1Components.size();
	auto dummy_2ComponentsCount = dummy_2Components.size();
	auto dummy_3ComponentsCount = dummy_3Components.size();

	ASSERT_EQ(expectedDummy_1Count, dummy_1ComponentsCount);
	ASSERT_EQ(expectedDummy_2Count, dummy_2ComponentsCount);
	ASSERT_EQ(expectedDummy_3Count, dummy_3ComponentsCount);
}

TEST_F(ZtComponentsManagerTests, getComponentsByTypeTest) {

	auto expectedComponentsCount = 3u;
	zt::Identificator expectedOwnerId(23u);

	feedComponentsManager<Dummy_1>(expectedOwnerId, expectedComponentsCount);
	auto components = componentsManager.getComponentsByType<Dummy_1>();
	auto componentsCount = components.size();

	ASSERT_EQ(expectedComponentsCount, componentsCount);

}

TEST_F(ZtComponentsManagerTests, addComponentTest) {

	zt::Identificator expectedId(232u);
	zt::Component::Tag expectedTag("expectedTag");
	auto expectedComponentsCount = 1u;

	Dummy_1 component(expectedId);
	component.setTag(expectedTag);

	auto addedComponent = componentsManager.addComponent<Dummy_1>(component);

	auto components = componentsManager.getComponentsByType<Dummy_1>();

	auto componentsCount = components.size();

	ASSERT_EQ(expectedComponentsCount, componentsCount);

	auto resultComponent = *components.begin();
	auto id = resultComponent.getOwnerIdentificator();
	auto tag = resultComponent.getTag();

	ASSERT_EQ(expectedId, id);
	ASSERT_EQ(expectedTag, tag);

}

TEST_F(ZtComponentsManagerTests, getComponentByIdentificatorTest) {

	zt::Identificator expectedOwnerId;
	auto component = componentsManager.createComponent<Dummy_1>(expectedOwnerId);
	auto componentId = component->getIdentificator();

	component = componentsManager.getComponentByIdentificator<Dummy_1>(componentId);
	
	auto componentOwnerId = component->getOwnerIdentificator();

	ASSERT_EQ(expectedOwnerId, componentOwnerId);

}

TEST_F(ZtComponentsManagerTests, getComponentByIdentificatorThrowTest) {

	auto expectedComponentAddress = nullptr;

	zt::Identificator componentId(100u);
	ASSERT_THROW(componentsManager.getComponentByIdentificator<Dummy_1>(componentId), zt::MainException);
}

TEST_F(ZtComponentsManagerTests, removeComponentTest) {

	auto expectedComponentsCount = 0u;
	
	auto ownerId = zt::Identificator();
	auto component = componentsManager.createComponent<Dummy_1>(ownerId);
	auto componentId = component->getIdentificator();

	auto isRemoved = componentsManager.removeComponentByIdentificator<Dummy_1>(componentId);
	
	ASSERT_TRUE(isRemoved);
	
	auto& components = componentsManager.getComponentsByType<Dummy_1>();
	auto componentsCount = components.size();
	
	ASSERT_EQ(expectedComponentsCount, componentsCount);

}

TEST_F(ZtComponentsManagerTests, removeAllComponentsByEntityOwnerIdentificatorTest) {

	auto expectedRemovedComponentsCount = 10u;
	auto ownerId = zt::Identificator();

	auto dummy_1Count = 6u;
	feedComponentsManager<Dummy_1>(ownerId, dummy_1Count);

	auto dummy_2Count = 4u;
	feedComponentsManager<Dummy_2>(ownerId, dummy_2Count);

	auto removedComponentsCount = componentsManager.removeAllComponentsByEntityOwnerIdentificator(ownerId);

	ASSERT_EQ(expectedRemovedComponentsCount, removedComponentsCount);
}

TEST_F(ZtComponentsManagerTests, removeComponentByIteratorTest) {

	auto ownerId = zt::Identificator();
	auto component = componentsManager.createComponent<Dummy_1>(ownerId);

	componentsManager.removeComponentByIterator<Dummy_1>(component);
}

TEST_F(ZtComponentsManagerTests, removeComponentByIteratorThrowTest) {

	auto ownerId = zt::Identificator();
	auto component = componentsManager.createComponent<Dummy_1>(ownerId);

	componentsManager.removeComponentByIterator<Dummy_1>(component);
}