#pragma once

#include "Zinet/GraphicLayer/ZtGLSemaphore.hpp"
#include "Zinet/GraphicLayer/ZtGLContext.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

#include "Zinet/Window/ZtGLFW.hpp"
#include "Zinet/Window/ZtWindow.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class SemaphoreTests : public ::testing::Test
	{
	protected:

		Context context;
		Instance instance;
		wd::Window window;
		Surface surface;
		PhysicalDevice physicalDevice;
		Device device;
		Semaphore semaphore;

		void SetUp() override
		{
			wd::GLFW::Init();

			vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
			instance.populateRequiredExtensions();
			vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
			instance.create(context, instanceCreateInfo);
			window.create();
			surface.create(instance, window);
			physicalDevice.create(instance);

			vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
			vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
			device.create(physicalDevice, deviceCreateInfo);
		}
		
		void TearDown() override
		{
			wd::GLFW::Deinit();
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