#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"

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

		void createShaders();
		void createDescriptors();
	};
	
	TEST_F(RendererTests, Initialize)
	{
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
	}

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
		const std::optional<PipelineLayout>& pipelineLayout = renderer.getPipelineLayout();
		ASSERT_FALSE(pipelineLayout.has_value());
	}

	TEST_F(RendererTests, GetRenderPass)
	{
		const RenderPass& renderPass = renderer.getRenderPass();
		ASSERT_EQ(renderPass, nullptr);
	}

	TEST_F(RendererTests, GetPipeline)
	{
		const std::optional<Pipeline>& pipeline = renderer.getPipeline();
		ASSERT_FALSE(pipeline.has_value());
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
		typedef const std::optional<DescriptorPool>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorPool);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	
		[[maybe_unused]] const std::optional<DescriptorPool>& descriptorPool = renderer.getDescriptorPool();
	}

	TEST_F(RendererTests, GetDescriptorSets)
	{
		typedef const std::optional<DescriptorSets>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorSets);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		[[maybe_unused]] const std::optional<DescriptorSets>& descriptorSets = renderer.getDescriptorSets();
	}
	
	TEST_F(RendererTests, PrepareDraw)
	{
		createShaders();
		createDescriptors();

		typedef void(Renderer::* ExpectedFunctionDeclaration)(const DrawInfo&);
		using FunctionDeclaration = decltype(&Renderer::prepareDraw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		renderer.initialize();
		DrawInfo drawInfo;
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		renderer.prepareDraw(drawInfo);
		renderer.prepareDraw(drawInfo);

		const std::vector<ShaderModule>& shadersModules = renderer.getShadersModules();
		ASSERT_EQ(shadersModules.size(), 2u);

		const std::vector<vk::PipelineShaderStageCreateInfo>& shadersStages = renderer.getShadersStages();
		ASSERT_EQ(shadersStages.size(), 2u);

		const std::vector<DescriptorSetLayout>& descriptorSetLayouts = renderer.getDescriptorSetLayouts();
		ASSERT_EQ(descriptorSetLayouts.size(), 1u);

		const std::optional<PipelineLayout>& pipelineLayout = renderer.getPipelineLayout();
		ASSERT_NE(pipelineLayout, nullptr);

		const std::optional<Pipeline>& pipeline = renderer.getPipeline();
		ASSERT_NE(pipeline, nullptr);

		const std::optional<DescriptorPool>& descriptorPool = renderer.getDescriptorPool();
		ASSERT_TRUE(descriptorPool.has_value());
		ASSERT_NE(descriptorPool, nullptr);

		const std::optional<DescriptorSets>& descriptorSets = renderer.getDescriptorSets();
		ASSERT_TRUE(descriptorSets.has_value());
		ASSERT_FALSE(descriptorSets->empty());
	}
	
	// TODO: Complete draw call
}

#include "ZtGLRendererTests.inl"