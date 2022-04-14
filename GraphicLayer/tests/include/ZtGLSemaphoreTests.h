#pragma once

#include "Zinet/GraphicLayer/ZtGLSemaphore.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class SemaphoreTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Semaphore semaphore;

		void SetUp() override
		{
			GLFW::InitGLFW();
		
			instance.createInstanceCreateInfo();
			instance.create(context);
		
			window.create();
		
			surface.create(instance, window);
		
			physicalDevice.create(instance);
		
			device.create(physicalDevice, surface);
		}
		
		void TearDown() override
		{
			GLFW::DeinitGLFW();
		}
	};

	TEST(Semaphore, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Semaphore, VulkanObject<vk::raii::Semaphore>>);
	}

	TEST(Semaphore, CreateSemaphoreCreateInfoTest)
	{
		Semaphore semaphore;
		vk::SemaphoreCreateInfo createInfo = semaphore.createSemaphoreCreateInfo();
	
		ASSERT_EQ(createInfo, vk::SemaphoreCreateInfo{});
	}
	
	TEST_F(SemaphoreTests, CreateTest)
	{
		semaphore.create(device);
	
		ASSERT_NE(*semaphore.getInternal(), *vk::raii::Semaphore{ std::nullptr_t{} });
	}
	
	TEST_F(SemaphoreTests, GetStatusTest)
	{
		semaphore.create(device);
		//uint64_t counterValue = semaphore.getCounterValue(); // Semaphore must be created as timeline
	
		//ASSERT_EQ(counterValue, 0u);
	}
}