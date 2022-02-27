#pragma once

#include "Zinet/GraphicLayer/ZtGLGraphicsPipeline.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class GraphicsPipelineTests : public ::testing::Test
	{
	protected:

		std::unique_ptr<GraphicsPipeline> graphicsPipeline = std::make_unique<GraphicsPipeline>();

	};

	TEST_F(GraphicsPipelineTests, CreateGraphicsPipelineCreateInfoTest)
	{
		PipelineLayout pipelineLayout;
		RenderPass renderPass;
		std::vector<vk::PipelineShaderStageCreateInfo> stages;
		vk::GraphicsPipelineCreateInfo createInfo = graphicsPipeline->createGraphicsPipelineCreateInfo(pipelineLayout, renderPass, stages);

		ASSERT_NE(createInfo, vk::GraphicsPipelineCreateInfo{});
	}

	TEST_F(GraphicsPipelineTests, GetInternalTest)
	{
		vk::raii::Pipeline& internal = graphicsPipeline->getInternal();

		ASSERT_EQ(*internal, *vk::raii::Pipeline{ std::nullptr_t{} });
	}

	TEST_F(GraphicsPipelineTests, CreateTest)
	{
		GLFW::InitGLFW();

		Context context;
		Instance instance;
		instance.createInstanceCreateInfo();
		instance.create(context);

		Window window;
		window.createWindow();

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
		renderPass.create(device);

		PipelineLayout pipelineLayout;
		pipelineLayout.createPipelineLayout(device);

		Shader vertexShader;
		vertexShader.setType(ShaderType::Vertex);
		vertexShader.loadFromFile(ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/shader.vert");
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

		vk::GraphicsPipelineCreateInfo createInfo = graphicsPipeline->createGraphicsPipelineCreateInfo(pipelineLayout, renderPass, stages);
		graphicsPipeline->create(device, createInfo);

		graphicsPipeline.reset();

		surface.destroy(instance);

		GLFW::DeinitGLFW();
	}

}