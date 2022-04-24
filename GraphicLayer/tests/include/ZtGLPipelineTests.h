#pragma once

#include "Zinet/GraphicLayer/ZtGLPipeline.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"

#include "gtest/gtest.h"

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
		vk::GraphicsPipelineCreateInfo createInfo = pipeline->createGraphicsPipelineCreateInfo(pipelineLayout, renderPass, stages);

		ASSERT_NE(createInfo, vk::GraphicsPipelineCreateInfo{});
	}

	TEST_F(PipelineTests, CreateTest)
	{
		GLFW::InitGLFW();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Window window;
		window.create();

		Surface surface;
		surface.create(instance, window);

		PhysicalDevice physicalDevice;
		physicalDevice.create(instance);

		Device device;
		device.create(physicalDevice, surface);

		RenderPass renderPass;
		renderPass.createAttachmentDescription(vk::Format::eR8G8Unorm);
		renderPass.createAttachmentReference();
		renderPass.createSubpassDescription();
		renderPass.createSubpassDependency();
		renderPass.create(device);

		PipelineLayout pipelineLayout;
		pipelineLayout.create(device);

		Shader vertexShader;
		vertexShader.setType(ShaderType::Vertex);
		vertexShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shaderStaticVertices.vert");
		vertexShader.compile();

		Shader fragmentShader;
		fragmentShader.setType(ShaderType::Fragment);
		fragmentShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.frag");
		fragmentShader.compile();

		ShaderModule vertexShaderModule;
		vertexShaderModule.create(device, vertexShader);

		ShaderModule fragmentShaderModule;
		fragmentShaderModule.create(device, fragmentShader);

		vk::PipelineShaderStageCreateInfo vertexShaderStage = pipelineLayout.createShaderStageCreateInfo(vertexShaderModule);
		vk::PipelineShaderStageCreateInfo fragmentShaderStage = pipelineLayout.createShaderStageCreateInfo(fragmentShaderModule);

		std::vector<vk::PipelineShaderStageCreateInfo> stages = { vertexShaderStage, fragmentShaderStage };

		vk::GraphicsPipelineCreateInfo createInfo = pipeline->createGraphicsPipelineCreateInfo(pipelineLayout, renderPass, stages);
		pipeline->create(device, createInfo);

		pipeline.reset();

		GLFW::DeinitGLFW();
	}

}