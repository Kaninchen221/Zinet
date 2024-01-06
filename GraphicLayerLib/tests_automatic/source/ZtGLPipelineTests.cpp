#pragma once

#include "Zinet/GraphicLayer/ZtGLPipeline.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderPass.hpp"
#include "Zinet/GraphicLayer/ZtGLContext.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLSurface.hpp"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLPipelineLayout.hpp"
#include "Zinet/GraphicLayer/ZtGLShader.hpp"
#include "Zinet/GraphicLayer/ZtGLShaderModule.hpp"

#include "Zinet/Window/ZtWindow.hpp"
#include "Zinet/Window/ZtGLFW.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class PipelineTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<Pipeline> pipeline = std::make_unique<Pipeline>();

	};

	TEST(Pipeline, DerivedFromVulkanObject)
	{
		static_assert(std::derived_from<Pipeline, VulkanObject<vk::raii::Pipeline>>);
	}

	TEST_F(PipelineTests, CreateGraphicsPipelineCreateInfoTest)
	{
		PipelineLayout pipelineLayout;
		RenderPass renderPass;
		std::vector<vk::PipelineShaderStageCreateInfo> stages;
		vk::GraphicsPipelineCreateInfo createInfo = pipeline->createGraphicsPipelineCreateInfo<Vertex>(pipelineLayout, renderPass, stages);

		ASSERT_NE(createInfo, vk::GraphicsPipelineCreateInfo{});
	}

	TEST_F(PipelineTests, CreateTest)
	{
		wd::GLFW::Init();

		Context context;
		Instance instance;
		vk::ApplicationInfo applicationInfo = instance.createApplicationInfo();
		instance.populateRequiredExtensions();
		vk::InstanceCreateInfo instanceCreateInfo = instance.createInstanceCreateInfo(applicationInfo);
		instance.create(context, instanceCreateInfo);

		wd::Window window;
		window.create();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		Device device;
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo = device.createDeviceQueueCreateInfo(physicalDevice, surface);
		vk::DeviceCreateInfo deviceCreateInfo = device.createDeviceCreateInfo(instance, physicalDevice, surface, deviceQueueCreateInfo);
		device.create(physicalDevice, deviceCreateInfo);

		RenderPass renderPass;
		renderPass.createColorAttachmentDescription(vk::Format::eR8G8Unorm);
		renderPass.createColorAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();

		vk::RenderPassCreateInfo renderPassCreateInfo = renderPass.createRenderPassCreateInfo();
		renderPass.create(device, renderPassCreateInfo);

		PipelineLayout pipelineLayout;
		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo = pipelineLayout.createPipelineLayoutCreateInfo();
		pipelineLayout.create(device, pipelineLayoutCreateInfo);

		Shader vertexShader;
		vertexShader.setType(ShaderType::Vertex);
		vertexShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shaderStaticVertices.vert");
		vertexShader.compile();

		Shader fragmentShader;
		fragmentShader.setType(ShaderType::Fragment);
		fragmentShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shaderStaticVertices.frag");
		fragmentShader.compile();

		ShaderModule vertexShaderModule;
		vk::ShaderModuleCreateInfo vertexShaderCreateInfo = vertexShaderModule.createShaderModuleCreateInfo(vertexShader);
		vertexShaderModule.create(device, ShaderType::Vertex, vertexShaderCreateInfo);

		ShaderModule fragmentShaderModule;
		vk::ShaderModuleCreateInfo fragmentShaderCreateInfo = fragmentShaderModule.createShaderModuleCreateInfo(fragmentShader);
		fragmentShaderModule.create(device, ShaderType::Fragment, fragmentShaderCreateInfo);

		vk::PipelineShaderStageCreateInfo vertexShaderStage = pipelineLayout.createShaderStageCreateInfo(vertexShaderModule);
		vk::PipelineShaderStageCreateInfo fragmentShaderStage = pipelineLayout.createShaderStageCreateInfo(fragmentShaderModule);

		std::vector<vk::PipelineShaderStageCreateInfo> stages = { vertexShaderStage, fragmentShaderStage };

		vk::GraphicsPipelineCreateInfo createInfo = pipeline->createGraphicsPipelineCreateInfo<Vertex>(pipelineLayout, renderPass, stages);
		pipeline->create(device, createInfo);

		pipeline.reset();

		wd::GLFW::Deinit();
	}

}