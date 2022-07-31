#pragma once

#include "Zinet/GraphicLayer/ZtGLShaderModule.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"

#include "gtest/gtest.h"

#include <memory>

namespace zt::gl::tests
{

	class ShaderModuleTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<ShaderModule> shaderModule;

		ShaderModuleTests()
			: shaderModule(std::make_unique<ShaderModule>())
		{
			//shaderModule = std::make_unique<ShaderModule>(shaderModule);
		}

		const char* cStringVertexShaderSource =
			"#version 330 core \n"
			"layout(location = 0) in vec3 aPos; \n"
			" \n"
			"void main() \n"
			"{ \n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
			"} \n\0";
	};

	TEST(ShaderModule, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<ShaderModule, VulkanObject<vk::raii::ShaderModule>>);
	}

	TEST_F(ShaderModuleTests, GetTypeTest)
	{
		ShaderType shaderType = shaderModule->getType();

		ASSERT_EQ(shaderType, ShaderType::Invalid);
	}

	TEST_F(ShaderModuleTests, CreateShaderModuleCreateInfoTest)
	{
		Shader shader;
		shader.loadFromCString(cStringVertexShaderSource);
		shader.setType(ShaderType::Vertex);
		shader.compile();
		vk::ShaderModuleCreateInfo createInfo = shaderModule->createShaderModuleCreateInfo(shader);

		ASSERT_NE(createInfo, vk::ShaderModuleCreateInfo{});
	}

	TEST_F(ShaderModuleTests, CreateTest)
	{
		GLFW::Init();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.getRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		Window window;
		window.create();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		std::unique_ptr<Device> device = std::make_unique<Device>();
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device->createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device->createDeviceCreateInfo(physicalDevice, surface, deviceQueueCreateInfo);
		device->create(physicalDevice, deviceCreateInfo);

		Shader shader;
		shader.loadFromCString(cStringVertexShaderSource);
		shader.setType(ShaderType::Vertex);
		shader.compile();

		vk::ShaderModuleCreateInfo createInfo = shaderModule->createShaderModuleCreateInfo(shader);
		shaderModule->create(*device, ShaderType::Vertex, createInfo);

		GLFW::Deinit();

		shaderModule.reset();
		device.reset();
	}

}