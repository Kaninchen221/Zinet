#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Zinet/Main/ECRS/ZtEntity.h"

#include "mocks/ZtComponentMock.h"
#include "mocks/ZtResourceMock.h"

class EntityTests : public ::testing::Test {
protected:

    EntityTests() {
    }

    ~EntityTests() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    zt::Entity::ComponentPtr AddComponentToEntity(zt::Entity& entity, const std::string& componentName);
    zt::Entity::ResourcePtr AddResourceToEntity(zt::Entity& entity, const std::string& resourceName);

    zt::Entity entity;
};

TEST_F(EntityTests, ConstructorTest) {
    zt::Entity entity;
}

TEST_F(EntityTests, AddComponentTest) {
    std::string componentName = "componentName";

    auto component = EntityTests::AddComponentToEntity(entity, componentName);

    auto componentFromGet = entity.getComponent(componentName);

    ASSERT_EQ(component.get(), componentFromGet.get());

    size_t expectedComponentsCount = 1;
    ASSERT_EQ(entity.componentsCount(), expectedComponentsCount);
}

TEST_F(EntityTests, RemoveComponentTest) {
    std::string componentName = "componentName";

    auto component = EntityTests::AddComponentToEntity(entity, componentName);

    bool resultOfRemove = entity.removeComponent(componentName);
    ASSERT_TRUE(resultOfRemove);

    size_t expectedComponentsCount = 0;
    ASSERT_EQ(entity.componentsCount(), expectedComponentsCount);
}

zt::Entity::ComponentPtr EntityTests::AddComponentToEntity(zt::Entity& entity, const std::string& componentName)
{
    auto component = std::make_shared<ZtComponentMock>();
    bool resultOfAdd = entity.addComponent(componentName, component);

    if (resultOfAdd) {
        return component;
    }
    else {
        return nullptr;
    }

}

TEST_F(EntityTests, AddResourceTest) {
    std::string resourceName = "resourceName";

    auto resource = AddResourceToEntity(entity, resourceName);

    auto getResult = entity.getResource(resourceName);

    ASSERT_EQ(resource.get(), getResult.get());
    
    size_t expectedComponentsCount = 1;
    ASSERT_EQ(entity.resourcesCount(), expectedComponentsCount);
}

TEST_F(EntityTests, RemoveResourceTest) {
    std::string resourceName = "resourceName";

    auto resource = AddResourceToEntity(entity, resourceName);

    bool resultOfRemove = entity.removeResource(resourceName);
    ASSERT_TRUE(resultOfRemove);

    size_t expectedResourcesCount = 0;
    ASSERT_EQ(entity.resourcesCount(), expectedResourcesCount);
}

inline zt::Entity::ResourcePtr EntityTests::AddResourceToEntity(zt::Entity& entity, const std::string& resourceName)
{
    auto resource = std::make_shared<ZtResourceMock>();
    bool resultOfAdd = entity.addResource(resourceName, resource);

    if (resultOfAdd) {
        return resource;
    }
    else {
        return nullptr;
    }
}

TEST_F(EntityTests, CopyableTest) {

    std::string componentName = "c1";
    auto component = AddComponentToEntity(entity, componentName);
    size_t expectedComponentsCount = 1;

    std::string firstResourceName = "r1";
    std::string secondResourceName = "r2";
    auto firstResource = AddResourceToEntity(entity, firstResourceName);
    auto secondResource = AddResourceToEntity(entity, secondResourceName);
    size_t expectedResourcesCount = 2;

    zt::Entity copyOfEntity(entity);
    auto componentsCount = copyOfEntity.componentsCount();
    auto resourcesCount = copyOfEntity.resourcesCount();

    auto copyOfComponent = copyOfEntity.getComponent(componentName);
    ASSERT_NE(component.get(), copyOfComponent.get());

    auto copyOfFirstResource = copyOfEntity.getResource(firstResourceName);
    ASSERT_NE(firstResource.get(), copyOfFirstResource.get());

    ASSERT_EQ(componentsCount, expectedComponentsCount);
    ASSERT_EQ(resourcesCount, expectedResourcesCount);

}

TEST_F(EntityTests, MovableTest) {

    size_t expectedCountInMovedEntity = 1u;
    size_t expectedCountInSourceEntity = 0u;

    std::string componentName = "component";
    auto component = AddComponentToEntity(entity, componentName);

    std::string resourceName = "resource";
    auto resource = AddResourceToEntity(entity, resourceName);

    zt::Entity movedEntity(std::move(entity));

    ASSERT_EQ(movedEntity.componentsCount(), expectedCountInMovedEntity);
    ASSERT_EQ(movedEntity.resourcesCount(), expectedCountInMovedEntity);

    ASSERT_EQ(entity.componentsCount(), expectedCountInSourceEntity);
    ASSERT_EQ(entity.resourcesCount(), expectedCountInSourceEntity);
}