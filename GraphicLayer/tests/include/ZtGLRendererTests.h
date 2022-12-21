#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;
		std::vector<Shader> shaders;
		std::vector<DrawInfo::Descriptor> descriptors;
		VertexBuffer vertexBuffer;
		std::vector<Vertex> vertices;
		IndexBuffer indexBuffer;
		std::vector<std::uint16_t> indices;
		std::vector<UniformBuffer> uniformBuffers;
		
		std::vector<DrawInfo::Image> imageDrawInfos;
		std::vector<Image> images;
		std::vector<ImageBuffer> imageBuffers;
		std::vector<Sampler> samplers;
		std::vector<ImageView> imageViews;
		std::vector<vk::ImageLayout> imageLayouts;
		STBImage stbImage;

		void createShaders();
		void createDescriptors();
		void createVertexBuffer();
		void createIndexBuffer();
		void createUniformBuffers();
		void createImageDrawInfos();
		void copyImageBufferToImage(Image& image, ImageBuffer& imageBuffer);

		struct MVP
		{

		};
	};

	TEST(Renderer, Initialize)
	{
		Renderer renderer;
		renderer.initialize();

		const Instance& instance = renderer.getInstance();
		ASSERT_NE(instance, vk::raii::Instance(std::nullptr_t{}));

		const DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
		ASSERT_NE(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));

		const Window& window = renderer.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();
		ASSERT_NE(internalWindow, nullptr);

		const Surface& surface = renderer.getSurface();
		ASSERT_NE(surface, nullptr);

		const PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
		ASSERT_NE(physicalDevice, nullptr);

		std::uint32_t queueFamilyIndex = renderer.getQueueFamilyIndex();
		ASSERT_NE(queueFamilyIndex, std::numeric_limits<uint32_t>::max());

		const Device& device = renderer.getDevice();
		ASSERT_NE(device, nullptr);

		const Queue& queue = renderer.getQueue();
		ASSERT_NE(queue, nullptr);

		const SwapChain& swapChain = renderer.getSwapChain();
		ASSERT_NE(swapChain, nullptr);

		const std::vector<ImageView>& imageViews = renderer.getImageViews();
		ASSERT_FALSE(imageViews.empty());

		const vk::Extent2D& swapExtent = renderer.getSwapExtent();
		ASSERT_NE(swapExtent, vk::Extent2D{});

		const RenderPass& renderPass = renderer.getRenderPass();
		ASSERT_NE(renderPass, nullptr);

		const std::vector<Framebuffer>& framebuffers = renderer.getFramebuffers();
		ASSERT_FALSE(framebuffers.empty());

		const Vma& vma = renderer.getVma();
		ASSERT_NE(vma.getInternal(), nullptr);

		const CommandPool& commandPool = renderer.getCommandPool();
		ASSERT_NE(commandPool, nullptr);

		const CommandBuffer& commandBuffer = renderer.getCommandBuffer();
		ASSERT_EQ(commandBuffer, nullptr);
	}

	/*
	TEST_F(RendererTests, GetContext)
	{
		[[maybe_unused]] const Context& context = renderer.getContext();
	}

	TEST_F(RendererTests, GetInstance)
	{
		const Instance& instance = renderer.getInstance();
		ASSERT_EQ(instance, vk::raii::Instance(std::nullptr_t{}));
	}

	TEST_F(RendererTests, GetDebugUtilsMessenger)
	{
		const DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
		ASSERT_EQ(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));
	}

	TEST_F(RendererTests, GetWindow)
	{
		const Window& window = renderer.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();

		ASSERT_EQ(internalWindow, nullptr);
	}

	TEST_F(RendererTests, GetSurface)
	{
		const Surface& surface = renderer.getSurface();
		ASSERT_EQ(surface, nullptr);
	}

	TEST_F(RendererTests, GetPhysicalDevice)
	{
		const PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
		ASSERT_EQ(physicalDevice, nullptr);
	}

	TEST_F(RendererTests, GetQueueFamilyIndex)
	{
		std::uint32_t queueFamilyIndex = renderer.getQueueFamilyIndex();
		ASSERT_EQ(queueFamilyIndex, std::numeric_limits<uint32_t>::max());
	}

	TEST_F(RendererTests, GetDevice)
	{
		const Device& device = renderer.getDevice();
		ASSERT_EQ(device, nullptr);
	}

	TEST_F(RendererTests, GetQueue)
	{
		const Queue& queue = renderer.getQueue();
		ASSERT_EQ(queue, nullptr);
	}

	TEST_F(RendererTests, GetSwapChainSupportDetails)
	{
		[[maybe_unused]] const SwapChainSupportDetails& swapChainSupportDetails = renderer.getSwapChainSupportDetails();
	}

	TEST_F(RendererTests, GetSwapChain)
	{
		const SwapChain& swapChain = renderer.getSwapChain();
		ASSERT_EQ(swapChain, nullptr);
	}

	TEST_F(RendererTests, GetImageViews)
	{
		const std::vector<ImageView>& imageViews = renderer.getImageViews();
		ASSERT_TRUE(imageViews.empty());
	}

	TEST_F(RendererTests, GetSwapExtent)
	{
		const vk::Extent2D& swapExtent = renderer.getSwapExtent();
		ASSERT_EQ(swapExtent, vk::Extent2D{});
	}

	TEST_F(RendererTests, GetPipelineLayout)
	{
		typedef const PipelineLayout& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getPipelineLayout);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const PipelineLayout& pipelineLayout = renderer.getPipelineLayout();
		ASSERT_EQ(pipelineLayout, nullptr);
	}

	TEST_F(RendererTests, GetRenderPass)
	{
		const RenderPass& renderPass = renderer.getRenderPass();
		ASSERT_EQ(renderPass, nullptr);
	}

	TEST_F(RendererTests, GetPipeline)
	{
		typedef const Pipeline& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getPipeline);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const Pipeline& pipeline = renderer.getPipeline();
		ASSERT_EQ(pipeline, nullptr);
	}

	TEST_F(RendererTests, GetFramebuffers)
	{
		const std::vector<Framebuffer>& framebuffers = renderer.getFramebuffers();
		ASSERT_TRUE(framebuffers.empty());
	}

	TEST_F(RendererTests, GetVma)
	{
		typedef const Vma&(Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getVma);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const Vma& vma = renderer.getVma();
		ASSERT_EQ(vma.getInternal(), nullptr);
	}

	TEST_F(RendererTests, GetShadersModules)
	{
		typedef const std::vector<ShaderModule>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getShadersModules);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const std::vector<ShaderModule>& shadersModules = renderer.getShadersModules();
		ASSERT_TRUE(shadersModules.empty());
	}

	TEST_F(RendererTests, GetShadersStagesCreateInfo)
	{
		typedef const std::vector<vk::PipelineShaderStageCreateInfo>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getShadersStages);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		const std::vector<vk::PipelineShaderStageCreateInfo>& shadersStages = renderer.getShadersStages();
		ASSERT_TRUE(shadersStages.empty());
	}
	
	TEST_F(RendererTests, GetDescriptorSetLayouts)
	{
		typedef const std::vector<DescriptorSetLayout>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorSetLayouts);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] const std::vector<DescriptorSetLayout>& descriptorSetLayouts = renderer.getDescriptorSetLayouts();
	}
	
	TEST_F(RendererTests, GetDescriptorPool)
	{
		typedef const DescriptorPool& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorPool);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	
		[[maybe_unused]] const DescriptorPool& descriptorPool = renderer.getDescriptorPool();
	}

	TEST_F(RendererTests, GetDescriptorSets)
	{
		typedef const std::optional<DescriptorSets>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorSets);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] const std::optional<DescriptorSets>& descriptorSets = renderer.getDescriptorSets();
	}

	TEST_F(RendererTests, GetCommandPool)
	{
		typedef const CommandPool& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getCommandPool);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	
		[[maybe_unused]] const CommandPool& commandPool = renderer.getCommandPool();
	}

	TEST_F(RendererTests, GetCommandBuffer)
	{
		typedef const CommandBuffer& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getCommandBuffer);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	
		[[maybe_unused]] const CommandBuffer& commandBuffer = renderer.getCommandBuffer();
	}

	TEST_F(RendererTests, GetWriteDescriptorSets)
	{
		typedef const std::vector<vk::WriteDescriptorSet>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getWriteDescriptorSets);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] const std::vector<vk::WriteDescriptorSet>& writeDescriptorSets = renderer.getWriteDescriptorSets();
	}
	*/

	TEST_F(RendererTests, GetDescriptorBufferInfos)
	{
		typedef const std::vector<vk::DescriptorBufferInfo>&(Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorBufferInfos);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] const std::vector<vk::DescriptorBufferInfo>& descriptorBufferInfos = renderer.getDescriptorBufferInfos();
	}

	TEST_F(RendererTests, GetDescriptorImageInfos)
	{
		typedef const std::vector<vk::DescriptorImageInfo>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorImageInfos);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] const std::vector<vk::DescriptorImageInfo>& descriptorImageInfos = renderer.getDescriptorImageInfos();
	}

	TEST_F(RendererTests, PrepareDraw)
	{
		renderer.initialize();
		createShaders();
		createDescriptors();
		createUniformBuffers();
		createImageDrawInfos();

		typedef void(Renderer::* ExpectedFunctionDeclaration)(const DrawInfo&);
		using FunctionDeclaration = decltype(&Renderer::prepareDraw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		DrawInfo drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer };
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		drawInfo.uniformBuffers = uniformBuffers;
		drawInfo.images = imageDrawInfos;
		renderer.prepareDraw(drawInfo);
		renderer.prepareDraw(drawInfo);

		const std::vector<ShaderModule>& shadersModules = renderer.getShadersModules();
		ASSERT_EQ(shadersModules.size(), 2u);

		const std::vector<vk::PipelineShaderStageCreateInfo>& shadersStages = renderer.getShadersStages();
		ASSERT_EQ(shadersStages.size(), 2u);

		const std::vector<DescriptorSetLayout>& descriptorSetLayouts = renderer.getDescriptorSetLayouts();
		ASSERT_EQ(descriptorSetLayouts.size(), 1u);

		const PipelineLayout& pipelineLayout = renderer.getPipelineLayout();
		ASSERT_NE(pipelineLayout, nullptr);

		const Pipeline& pipeline = renderer.getPipeline();
		ASSERT_NE(pipeline, nullptr);

		const DescriptorPool& descriptorPool = renderer.getDescriptorPool();
		ASSERT_NE(descriptorPool, nullptr);

		const std::optional<DescriptorSets>& descriptorSets = renderer.getDescriptorSets();
		ASSERT_TRUE(descriptorSets.has_value());
		ASSERT_FALSE(descriptorSets->empty());

		const std::vector<vk::WriteDescriptorSet>& writeDescriptorSets = renderer.getWriteDescriptorSets();
		ASSERT_EQ(writeDescriptorSets.size(), 2u);

		const std::vector<vk::DescriptorBufferInfo>& descriptorBufferInfos = renderer.getDescriptorBufferInfos();
		ASSERT_EQ(descriptorBufferInfos.size(), 1u);

		const std::vector<vk::DescriptorImageInfo>& descriptorImageInfos = renderer.getDescriptorImageInfos();
		ASSERT_EQ(descriptorImageInfos.size(), 1u);
	}

	TEST_F(RendererTests, Draw)
	{
		zt::gl::GLFW::UnhideWindow();
		typedef void(Renderer::* ExpectedFunctionDeclaration)(const DrawInfo&);
		using FunctionDeclaration = decltype(&Renderer::draw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		renderer.initialize();

		createShaders();
		createDescriptors();
		createVertexBuffer();
		createIndexBuffer();
		createUniformBuffers();
		createImageDrawInfos();

		DrawInfo drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer };
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		drawInfo.uniformBuffers = uniformBuffers;
		drawInfo.images = imageDrawInfos;
		renderer.prepareDraw(drawInfo);
		renderer.draw(drawInfo);

		// Resolve runtime errors
		renderer.getQueue()->waitIdle();
	}
}

#include "ZtGLRendererTests.inl"