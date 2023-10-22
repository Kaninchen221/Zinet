#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

#include "Zinet/Window/ZtGLFW.h"

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

		static_assert(std::is_default_constructible_v<Renderer>);
		static_assert(!std::is_copy_constructible_v<Renderer>);
		static_assert(!std::is_copy_assignable_v<Renderer>);
		static_assert(std::is_move_constructible_v<Renderer>);
		static_assert(std::is_move_assignable_v<Renderer>);
		static_assert(std::is_destructible_v<Renderer>);

		std::vector<Shader> shaders;
		std::vector<RenderStates::Descriptor> descriptors;
		VertexBuffer vertexBuffer;
		std::vector<Vertex> vertices;
		IndexBuffer indexBuffer;
		std::vector<std::uint16_t> indices;
		std::vector<UniformBuffer> uniformBuffers;
		
		std::vector<RenderStates::Image> imageRenderStates;
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
		RendererContext& rendererContext = renderer.getRendererContext();

		const Instance& instance = rendererContext.getInstance();
		ASSERT_NE(instance, vk::raii::Instance(std::nullptr_t{}));

		const DebugUtilsMessenger& debugUtilsMessenger = rendererContext.getDebugUtilsMessenger();
		ASSERT_NE(debugUtilsMessenger, vk::raii::DebugUtilsMessengerEXT(std::nullptr_t{}));

		const wd::Window& window = rendererContext.getWindow();
		const GLFWwindow* internalWindow = window.getInternal();
		ASSERT_NE(internalWindow, nullptr);

		const Surface& surface = rendererContext.getSurface();
		ASSERT_NE(surface, nullptr);

		const PhysicalDevice& physicalDevice = rendererContext.getPhysicalDevice();
		ASSERT_NE(physicalDevice, nullptr);

		std::uint32_t queueFamilyIndex = rendererContext.getQueueFamilyIndex();
		ASSERT_NE(queueFamilyIndex, std::numeric_limits<uint32_t>::max());

		const Device& device = rendererContext.getDevice();
		ASSERT_NE(device, nullptr);

		const Queue& queue = rendererContext.getQueue();
		ASSERT_NE(queue, nullptr);

		const SwapChain& swapChain = rendererContext.getSwapChain();
		ASSERT_NE(swapChain, nullptr);

		const vk::Extent2D& swapExtent = rendererContext.getSwapExtent();
		ASSERT_NE(swapExtent, vk::Extent2D{});

		const RenderPass& renderPass = rendererContext.getRenderPass();
		ASSERT_NE(renderPass, nullptr);

		const std::vector<RenderTargetDisplay>& renderTargets = rendererContext.getRenderTargets();
		ASSERT_FALSE(renderTargets.empty());

		const Vma& vma = rendererContext.getVma();
		ASSERT_NE(vma.getInternal(), nullptr);

		const CommandPool& commandPool = rendererContext.getCommandPool();
		ASSERT_NE(commandPool, nullptr);
	}

	TEST_F(RendererTests, preDraw)
	{
		renderer.initialize();

		typedef void(Renderer::* ExpectedFunctionDeclaration)();
		using FunctionDeclaration = decltype(&Renderer::preDraw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		renderer.preDraw();
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
		RenderStates::Descriptor descriptor;
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

		RendererContext& rendererContext = renderer.getRendererContext();
		Buffer::CreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
			rendererContext.getVma(),
			vertexBuffer.createCreateInfo(vertices.size() * sizeof(Vertex)),
			vertexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		vertexBuffer.create(bufferCreateInfo);
	}

	void RendererTests::createIndexBuffer()
	{
		RendererContext& rendererContext = renderer.getRendererContext();
		indices = { 0, 1, 2, 2, 3, 0 };

		Buffer::CreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
			rendererContext.getVma(),
			indexBuffer.createCreateInfo(indices.size() * sizeof(std::uint16_t)),
			indexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		indexBuffer.create(bufferCreateInfo);
	}

	void RendererTests::createUniformBuffers()
	{
		RendererContext& rendererContext = renderer.getRendererContext();

		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		Buffer::CreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(MVP)),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.setBinding(0u);
	}

	void RendererTests::createImageDrawInfos()
	{
		RendererContext& rendererContext = renderer.getRendererContext();

		if (!stbImage.load((ContentPath / "texture.jpg").string()))
		{
			FAIL() << "Can't load texture image";
			return;
		}

		Vector2<std::uint32_t> size = { stbImage.getWidth(), stbImage.getHeight() };

		Image& image = images.emplace_back();
		Image::CreateInfo imageCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(size),
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		ImageBuffer& imageBuffer = imageBuffers.emplace_back();
		Buffer::CreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = imageBuffer.createCreateInfo(stbImage.sizeBytes()),
			.allocationCreateInfo = imageBuffer.createVmaAllocationCreateInfo(false, true)
		};
		imageBuffer.create(bufferCreateInfo);

		copyImageBufferToImage(image, imageBuffer);

		Sampler& sampler = samplers.emplace_back();
		vk::SamplerCreateInfo samplerCreateInfo = sampler.createCreateInfo();
		sampler.create(rendererContext.getDevice(), samplerCreateInfo);

		ImageView& view = imageViews.emplace_back();
		std::uint32_t mipmapLevels = 1u;
		vk::ImageViewCreateInfo imageViewCreateInfo = view.createCreateInfo(*image.getInternal(), mipmapLevels, vk::Format::eR8G8B8A8Srgb);
		view.create(rendererContext.getDevice(), imageViewCreateInfo);

		vk::ImageLayout imageLayout = imageLayouts.emplace_back(vk::ImageLayout::eShaderReadOnlyOptimal);
		RenderStates::Image& imageRenderState = imageRenderStates.emplace_back(imageBuffer, sampler, view, imageLayout);
		imageRenderState.binding = 1u;

	}

	void RendererTests::copyImageBufferToImage(Image& image, ImageBuffer& imageBuffer)
	{
		RendererContext& rendererContext = renderer.getRendererContext();

		CommandBuffer commandBuffer;
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());

		// Barrier
		vk::ImageLayout newLayout = vk::ImageLayout::eTransferDstOptimal;
		vk::PipelineStageFlags destinationStage = vk::PipelineStageFlagBits::eFragmentShader;

		commandBuffer.begin();
		image.changeLayout(commandBuffer, newLayout, destinationStage);
		commandBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		rendererContext.getQueue().submit(submitInfo);
		rendererContext.getQueue()->waitIdle();

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

		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());

		commandBuffer.begin();

		newLayout = vk::ImageLayout::eTransferDstOptimal;
		CommandBuffer::CopyBufferToImageInfo copyBufferToImageInfo
		{
			imageBuffer, image, newLayout, imageRegion
		};
		commandBuffer.copyBufferToImage(copyBufferToImageInfo);

		commandBuffer.end();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		rendererContext.getQueue().submit(submitInfo);
		rendererContext.getQueue()->waitIdle();

		// Barrier after copy
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());

		commandBuffer.begin();

		newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		destinationStage = vk::PipelineStageFlagBits::eFragmentShader;
		image.changeLayout(commandBuffer, newLayout, destinationStage);

		commandBuffer.end();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*commandBuffer.getInternal();

		rendererContext.getQueue().submit(submitInfo);
		rendererContext.getQueue()->waitIdle();
	}
}