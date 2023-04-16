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
	}

	TEST(Renderer, GetContext)
	{
		Renderer renderer;
		[[maybe_unused]] const Context& context = renderer.getContext();
	}

	TEST(Renderer, GetInstance)
	{
		Renderer renderer;
		const Instance& instance = renderer.getInstance();
		ASSERT_EQ(instance, vk::raii::Instance(std::nullptr_t{}));
	}

	TEST(Renderer, GetDebugUtilsMessenger)
	{
		Renderer renderer;
		const DebugUtilsMessenger& debugUtilsMessenger = renderer.getDebugUtilsMessenger();
		ASSERT_EQ(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));
	}

	TEST(Renderer, GetWindow)
	{
		Renderer renderer;
		const Window& window = renderer.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();

		ASSERT_EQ(internalWindow, nullptr);
	}

	TEST(Renderer, GetSurface)
	{
		Renderer renderer;
		const Surface& surface = renderer.getSurface();
		ASSERT_EQ(surface, nullptr);
	}

	TEST(Renderer, GetPhysicalDevice)
	{
		Renderer renderer;
		const PhysicalDevice& physicalDevice = renderer.getPhysicalDevice();
		ASSERT_EQ(physicalDevice, nullptr);
	}

	TEST(Renderer, GetQueueFamilyIndex)
	{
		Renderer renderer;
		std::uint32_t queueFamilyIndex = renderer.getQueueFamilyIndex();
		ASSERT_EQ(queueFamilyIndex, std::numeric_limits<uint32_t>::max());
	}

	TEST(Renderer, GetDevice)
	{
		Renderer renderer;
		const Device& device = renderer.getDevice();
		ASSERT_EQ(device, nullptr);
	}

	TEST(Renderer, GetQueue)
	{
		Renderer renderer;
		const Queue& queue = renderer.getQueue();
		ASSERT_EQ(queue, nullptr);
	}

	TEST(Renderer, GetSwapChainSupportDetails)
	{
		Renderer renderer;
		[[maybe_unused]] const SwapChainSupportDetails& swapChainSupportDetails = renderer.getSwapChainSupportDetails();
	}

	TEST(Renderer, GetSwapChain)
	{
		Renderer renderer;
		const SwapChain& swapChain = renderer.getSwapChain();
		ASSERT_EQ(swapChain, nullptr);
	}

	TEST(Renderer, GetImageViews)
	{
		Renderer renderer;
		const std::vector<ImageView>& imageViews = renderer.getImageViews();
		ASSERT_TRUE(imageViews.empty());
	}

	TEST(Renderer, GetSwapExtent)
	{
		Renderer renderer;
		const vk::Extent2D& swapExtent = renderer.getSwapExtent();
		ASSERT_EQ(swapExtent, vk::Extent2D{});
	}

	TEST(Renderer, GetPipelineLayout)
	{
		typedef const PipelineLayout& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getPipelineLayout);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		const PipelineLayout& pipelineLayout = renderer.getPipelineLayout();
		ASSERT_EQ(pipelineLayout, nullptr);
	}

	TEST(Renderer, GetRenderPass)
	{
		Renderer renderer;
		const RenderPass& renderPass = renderer.getRenderPass();
		ASSERT_EQ(renderPass, nullptr);
	}

	TEST(Renderer, GetPipeline)
	{
		typedef const Pipeline& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getPipeline);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		const Pipeline& pipeline = renderer.getPipeline();
		ASSERT_EQ(pipeline, nullptr);
	}

	TEST(Renderer, GetFramebuffers)
	{
		Renderer renderer;
		const std::vector<Framebuffer>& framebuffers = renderer.getFramebuffers();
		ASSERT_TRUE(framebuffers.empty());
	}

	TEST(Renderer, GetVma)
	{
		typedef const Vma&(Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getVma);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		const Vma& vma = renderer.getVma();
		ASSERT_EQ(vma.getInternal(), nullptr);
	}

	TEST(Renderer, GetShadersModules)
	{
		typedef const std::vector<ShaderModule>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getShadersModules);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		const std::vector<ShaderModule>& shadersModules = renderer.getShadersModules();
		ASSERT_TRUE(shadersModules.empty());
	}

	TEST(Renderer, GetShadersStagesCreateInfo)
	{
		typedef const std::vector<vk::PipelineShaderStageCreateInfo>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getShadersStages);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		const std::vector<vk::PipelineShaderStageCreateInfo>& shadersStages = renderer.getShadersStages();
		ASSERT_TRUE(shadersStages.empty());
	}
	
	TEST(Renderer, GetDescriptorSetLayouts)
	{
		typedef const std::vector<DescriptorSetLayout>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorSetLayouts);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		[[maybe_unused]] const std::vector<DescriptorSetLayout>& descriptorSetLayouts = renderer.getDescriptorSetLayouts();
	}
	
	TEST(Renderer, GetDescriptorPool)
	{
		typedef const DescriptorPool& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorPool);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		[[maybe_unused]] const DescriptorPool& descriptorPool = renderer.getDescriptorPool();
	}

	TEST(Renderer, GetDescriptorSets)
	{
		typedef const std::optional<DescriptorSets>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorSets);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		[[maybe_unused]] const std::optional<DescriptorSets>& descriptorSets = renderer.getDescriptorSets();
	}

	TEST(Renderer, GetCommandPool)
	{
		typedef const CommandPool& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getCommandPool);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		[[maybe_unused]] const CommandPool& commandPool = renderer.getCommandPool();
	}

	TEST(Renderer, GetWriteDescriptorSets)
	{
		typedef const std::vector<vk::WriteDescriptorSet>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getWriteDescriptorSets);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		[[maybe_unused]] const std::vector<vk::WriteDescriptorSet>& writeDescriptorSets = renderer.getWriteDescriptorSets();
	}

	TEST(Renderer, GetDescriptorBufferInfos)
	{
		typedef const std::vector<vk::DescriptorBufferInfo>&(Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorBufferInfos);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		[[maybe_unused]] const std::vector<vk::DescriptorBufferInfo>& descriptorBufferInfos = renderer.getDescriptorBufferInfos();
	}

	TEST(Renderer, GetDescriptorImageInfos)
	{
		typedef const std::vector<vk::DescriptorImageInfo>& (Renderer::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Renderer::getDescriptorImageInfos);
		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer renderer;
		[[maybe_unused]] const std::vector<vk::DescriptorImageInfo>& descriptorImageInfos = renderer.getDescriptorImageInfos();
	}

	TEST_F(RendererTests, preDraw)
	{
		renderer.initialize();

		typedef void(Renderer::* ExpectedFunctionDeclaration)();
		using FunctionDeclaration = decltype(&Renderer::preDraw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		renderer.preDraw();
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
		renderer.preDraw();
		renderer.draw(drawInfo);

		// Resolve runtime errors
		renderer.getQueue()->waitIdle();
	}

	void RendererTests::createShaders()
	{
		shaders.emplace_back();
		shaders[0].setType(ShaderType::Vertex);
		shaders[0].loadFromFile((ContentPath / "shader.vert").string());
		shaders[0].compile();

		shaders.emplace_back();
		shaders[1].setType(ShaderType::Fragment);
		shaders[1].loadFromFile((ContentPath / "shader.frag").string());
		shaders[1].compile();
	}

	void RendererTests::createDescriptors()
	{
		DrawInfo::Descriptor descriptor;
		descriptor.binding = 0;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		descriptor.binding = 1;
		descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Fragment;
		descriptors.push_back(descriptor);
	}

	void RendererTests::createVertexBuffer()
	{
		Vertex vertex;
		vertex.setPosition({ -0.5f, -0.5f, 0.f });
		vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates({ 1.0f, 0.0f });
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, -0.5f, 0.f });
		vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates({ 0.0f, 0.0f });
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, 0.5f, 0.f });
		vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		vertex.setTextureCoordinates({ 0.0f, 1.0f });
		vertices.push_back(vertex);

		vertex.setPosition({ -0.5f, 0.5f, 0.f });
		vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		vertex.setTextureCoordinates({ 1.0f, 1.0f });
		vertices.push_back(vertex);

		BufferCreateInfo bufferCreateInfo{
			renderer.getDevice(),
			renderer.getVma(),
			vertexBuffer.createCreateInfo(vertices.size() * sizeof(Vertex)),
			vertexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		vertexBuffer.create(bufferCreateInfo);
	}

	void RendererTests::createIndexBuffer()
	{
		indices = { 0, 1, 2, 2, 3, 0 };

		BufferCreateInfo bufferCreateInfo{
			renderer.getDevice(),
			renderer.getVma(),
			indexBuffer.createCreateInfo(indices.size() * sizeof(std::uint16_t)),
			indexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		indexBuffer.create(bufferCreateInfo);
	}

	void RendererTests::createUniformBuffers()
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(MVP)),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
	}

	void RendererTests::createImageDrawInfos()
	{
		if (!stbImage.load((ContentPath / "texture.jpg").string()))
		{
			FAIL() << "Can't load texture image";
			return;
		}

		Image& image = images.emplace_back();
		ImageCreateInfo imageCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(stbImage.getWidth(), stbImage.getHeight()),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		ImageBuffer& imageBuffer = imageBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(stbImage.sizeBytes()),
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
		};
		imageBuffer.create(bufferCreateInfo);

		copyImageBufferToImage(image, imageBuffer);

		Sampler& sampler = samplers.emplace_back();
		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(renderer.getDevice(), samplerCreateInfo);

		ImageView& view = imageViews.emplace_back();
		vk::ImageViewCreateInfo imageViewCreateInfo = view.createCreateInfo(*image.getInternal(), vk::Format::eR8G8B8A8Srgb);
		view.create(renderer.getDevice(), imageViewCreateInfo);

		vk::ImageLayout imageLayout = imageLayouts.emplace_back(vk::ImageLayout::eShaderReadOnlyOptimal);
		[[maybe_unused]] DrawInfo::Image& imageDrawInfo = imageDrawInfos.emplace_back(imageBuffer, sampler, view, imageLayout);

	}

	void RendererTests::copyImageBufferToImage(Image& image, ImageBuffer& imageBuffer)
	{
		CommandBuffer commandBuffer;
		//vk::CommandBufferAllocateInfo allocateInfo = commandBuffer.createCommandBufferAllocateInfo(commandPool);
		commandBuffer.allocateCommandBuffer(renderer.getDevice(), renderer.getCommandPool());

		// Barrier
		vk::ImageLayout oldLayout = vk::ImageLayout::eUndefined;
		vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
		vk::ImageMemoryBarrier barrier = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);

		vk::PipelineStageFlags sourceStage = vk::PipelineStageFlagBits::eTopOfPipe;

		vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

		commandBuffer.begin();

		commandBuffer->pipelineBarrier(
			sourceStage,
			destinationStage,
			vk::DependencyFlags{},
			{},
			{},
			barrier);

		commandBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		renderer.getQueue().submit(submitInfo);
		renderer.getQueue()->waitIdle();

		// BufferImageCopy
		vk::BufferImageCopy imageRegion{};
		imageRegion.bufferOffset = 0;
		imageRegion.bufferRowLength = 0;
		imageRegion.bufferImageHeight = 0;

		imageRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		imageRegion.imageSubresource.mipLevel = 0;
		imageRegion.imageSubresource.baseArrayLayer = 0;
		imageRegion.imageSubresource.layerCount = 1;

		imageRegion.imageOffset = vk::Offset3D{ 0, 0, 0 };
		imageRegion.imageExtent = vk::Extent3D{
			static_cast<std::uint32_t>(stbImage.getWidth()),
			static_cast<std::uint32_t>(stbImage.getHeight()),
			1
		};

		commandBuffer.allocateCommandBuffer(renderer.getDevice(), renderer.getCommandPool());

		commandBuffer.begin();

		newLayout = vk::ImageLayout::eTransferDstOptimal;
		commandBuffer.copyBufferToImage(imageBuffer, image, newLayout, imageRegion);
		commandBuffer.end();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		renderer.getQueue().submit(submitInfo);
		renderer.getQueue()->waitIdle();

		// Barrier after copy
		commandBuffer.allocateCommandBuffer(renderer.getDevice(), renderer.getCommandPool());

		commandBuffer.begin();

		oldLayout = vk::ImageLayout::eTransferDstOptimal;
		newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		vk::ImageMemoryBarrier barrierAfterCopy = commandBuffer.createImageMemoryBarrier(image, oldLayout, newLayout);

		sourceStage = vk::PipelineStageFlagBits::eTransfer;
		destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

		commandBuffer->pipelineBarrier(
			sourceStage,
			destinationStage,
			vk::DependencyFlags{},
			{},
			{},
			barrierAfterCopy);

		commandBuffer.end();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		renderer.getQueue().submit(submitInfo);
		renderer.getQueue()->waitIdle();
	}
}