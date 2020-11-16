#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ECRS/ZtComponent.h"

namespace zt {

	class ZtComponentTests : public ::testing::Test {
	protected:



	};

	TEST_F(ZtComponentTests, constructTest) {

		zt::Identificator expectedOwnerIdentificator(404u);
		zt::Component component(expectedOwnerIdentificator);

		auto componentOwnerIdentificator = component.getOwnerIdentificator();

		ASSERT_EQ(expectedOwnerIdentificator, componentOwnerIdentificator);
	}

	TEST_F(ZtComponentTests, setAndGetOwnerIdentificatorTest) {

		zt::Identificator expiredId(0u);
		zt::Component component(expiredId);

		zt::Identificator expectedId(4332u);
		component.setOwnerIdentificator(expectedId);

		auto componentId = component.getOwnerIdentificator();

		ASSERT_EQ(expectedId, componentId);
	}

	TEST_F(ZtComponentTests, setAndGetTagTest) {

		std::string expectedTag = "emptyComponent";

		zt::Identificator id(0u);
		zt::Component component(id);
		component.setTag(expectedTag);
		auto componentTag = component.getTag();
		
		ASSERT_EQ(expectedTag, componentTag);
	}

	TEST_F(ZtComponentTests, copyConstructorTest) {

		auto expectedId = zt::Identificator(323u);
		auto expectedTag = zt::Component::Tag("exampleTag");
		zt::Component component(expectedId);
		component.setTag(expectedTag);
		auto componentId = component.getIdentificator();

		zt::Component copy(component);
		auto identificator = copy.getOwnerIdentificator();
		auto copyTag = copy.getTag();
		auto copyId = copy.getIdentificator();
		
		ASSERT_EQ(expectedId, identificator);
		ASSERT_EQ(expectedTag, copyTag);
		ASSERT_NE(componentId, copyId);
	}

	TEST_F(ZtComponentTests, copyAssignOperatorTest) {

		auto expectedId = zt::Identificator(323u);
		auto expectedTag = zt::Component::Tag("exampleTag");
		zt::Component component(expectedId);
		component.setTag(expectedTag);
		auto componentId = component.getIdentificator();

		zt::Component copy(zt::Identificator(12u));
		copy = component;
		auto identificator = copy.getOwnerIdentificator();
		auto copyTag = copy.getTag();
		auto copyId = copy.getIdentificator();

		ASSERT_EQ(expectedId, identificator);
		ASSERT_EQ(expectedTag, copyTag);
		ASSERT_NE(componentId, copyId);
	}

	TEST_F(ZtComponentTests, moveConstructorTest) {

		auto expectedOwnerId = zt::Identificator(323u);
		auto expectedTag = zt::Component::Tag("exampleTag");
		zt::Component component(expectedOwnerId);
		component.setTag(expectedTag);
		auto expectedId = component.getIdentificator();

		zt::Component moved(std::move(component));
		auto movedOwnerIdentificator = moved.getOwnerIdentificator();
		auto movedTag = moved.getTag();
		auto movedId = moved.getIdentificator();

		ASSERT_EQ(expectedOwnerId, movedOwnerIdentificator);
		ASSERT_EQ(expectedTag, movedTag);
		ASSERT_EQ(expectedId, movedId);

		auto componentActualOwnerId = component.getOwnerIdentificator();
		auto componentActualId = component.getIdentificator();
		auto componentActualTag = component.getTag();

		ASSERT_EQ(expectedOwnerId, componentActualOwnerId);
		ASSERT_NE(expectedTag, componentActualTag);
		ASSERT_NE(expectedId, componentActualId);
	}

	TEST_F(ZtComponentTests, moveAssignOperatorTest) {

		auto expectedOwnerId = zt::Identificator(323u);
		auto expectedTag = zt::Component::Tag("exampleTag");
		zt::Component component(expectedOwnerId);
		component.setTag(expectedTag);
		auto expectedId = component.getIdentificator();

		zt::Component moved(zt::Identificator(12u));
		moved = std::move(component);
		auto movedOwnerIdentificator = moved.getOwnerIdentificator();
		auto movedTag = moved.getTag();
		auto movedId = moved.getIdentificator();

		ASSERT_EQ(expectedOwnerId, movedOwnerIdentificator);
		ASSERT_EQ(expectedTag, movedTag);
		ASSERT_EQ(expectedId, movedId);

		auto componentActualOwnerId = component.getOwnerIdentificator();
		auto componentActualId = component.getIdentificator();
		auto componentActualTag = component.getTag();

		ASSERT_EQ(expectedOwnerId, componentActualOwnerId);
		ASSERT_NE(expectedTag, componentActualTag);
		ASSERT_NE(expectedId, componentActualId);
	}

	TEST_F(ZtComponentTests, uniqueIdentificatorTest) {

		zt::Identificator id(0u);
		zt::Component component_1(id);
		zt::Component component_2(id);
		zt::Component component_3(component_1);
		
		auto uniqueId_1 = component_1.getIdentificator().getNumber();
		auto uniqueId_2 = component_2.getIdentificator().getNumber();
		auto uniqueId_3 = component_3.getIdentificator().getNumber();

		ASSERT_NE(uniqueId_1, uniqueId_2);
		ASSERT_NE(uniqueId_2, uniqueId_3);
	}

}