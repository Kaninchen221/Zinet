#pragma once

#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLImage.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLSTBImage.h"
#include "Zinet/GraphicLayer/ZtGLMVP.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>
#include <chrono>

namespace zt::gl::tests
{

	class RendererTests : public ::testing::Test
	{
	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("RendererTests");

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;

		struct DrawableObject 
		{
			DrawableObject() = delete;
			DrawableObject(const DrawableObject& other) = default;
			DrawableObject(DrawableObject&& other) = default;
			DrawableObject& operator = (const DrawableObject& other) = default;
			DrawableObject& operator = (DrawableObject& other) = default;
			~DrawableObject() noexcept;
			DrawableObject(Renderer& rendererRef) : renderer(rendererRef) {}

			std::vector<Shader> shaders;
			std::vector<DrawInfo::Descriptor> descriptors;
			VertexBuffer vertexBuffer;
			std::vector<Vertex> vertices;
			IndexBuffer indexBuffer;
			std::vector<std::uint16_t> indices;
			std::vector<UniformBuffer> uniformBuffers;

			// TODO Create Texture class
			std::vector<DrawInfo::Image> imageDrawInfos;
			std::vector<Image> images;
			std::vector<ImageBuffer> imageBuffers;
			std::vector<Sampler> samplers;
			std::vector<ImageView> imageViews;
			std::vector<vk::ImageLayout> imageLayouts;
			STBImage stbImage;
			MVP mvp;
			Renderer& renderer;

			void createShaders();
			void createDescriptors();
			void createVertexBuffer();
			void createIndexBuffer();
			void createUniformBuffers();
			void createImageDrawInfos();
			void copyImageBufferToImage(Image& image, ImageBuffer& imageBuffer);

			DrawInfo createDrawInfo();

			void rotateImage();
			void rotateImage2();
		};

	};

	TEST_F(RendererTests, Draw)
	{
		zt::gl::GLFW::UnhideWindow();
		typedef void(Renderer::* ExpectedFunctionDeclaration)(const DrawInfo&);
		using FunctionDeclaration = decltype(&Renderer::draw);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		renderer.initialize();

		int count = 2;
		std::vector<DrawableObject> drawableObjects;
		drawableObjects.reserve(count);
		std::vector<DrawInfo> drawInfos;
		drawInfos.reserve(count);
		for (size_t i = 0u; i < count; ++i)
		{
			drawableObjects.push_back(renderer);
			DrawableObject& drawableObject = drawableObjects[i];
			drawableObject.createShaders();
			drawableObject.createDescriptors();
			drawableObject.createVertexBuffer();
			drawableObject.createIndexBuffer();
			drawableObject.createUniformBuffers();
			drawableObject.createImageDrawInfos();

			drawInfos.push_back(drawableObject.createDrawInfo());
		}

		auto timeAtStartDrawing = std::chrono::high_resolution_clock::now();

		while (!renderer.getWindow().shouldBeClosed())
		{
			//Logger->info("preDraw");
			renderer.preDraw();

			//Logger->info("Draw 0");
			drawableObjects[0].rotateImage();
			renderer.draw(drawInfos[0]);

			//Logger->info("Draw 1");
			drawableObjects[1].rotateImage2();
			renderer.draw(drawInfos[1]);

			glfwPollEvents();

			//Logger->info("postDraw");
			renderer.postDraw();

			auto currentTime = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - timeAtStartDrawing).count();
			if (duration > 5)
			{
				glfwSetWindowShouldClose(renderer.getWindow().getInternal(), true);
			}
		}

		renderer.getQueue()->waitIdle();
		renderer.getDevice()->waitIdle();
	}

	RendererTests::DrawableObject::~DrawableObject() noexcept
	{
		shaders.clear();
		descriptors.clear();
		vertexBuffer.~VertexBuffer();
		indexBuffer.~IndexBuffer();
		uniformBuffers.clear();

		imageDrawInfos.clear();
		images.clear();
		imageBuffers.clear();
		samplers.clear();
		imageViews.clear();
		imageLayouts.clear();
		stbImage.~STBImage();
	}

	void RendererTests::DrawableObject::createShaders()
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

	void RendererTests::DrawableObject::createDescriptors()
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

	void RendererTests::DrawableObject::createVertexBuffer()
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
		vertexBuffer.fillWithStdContainer(vertices);
	}

	void RendererTests::DrawableObject::createIndexBuffer()
	{
		indices = { 0, 1, 2, 2, 3, 0 };
		std::uint64_t size = sizeof(decltype(indices)::value_type) * indices.size();

		BufferCreateInfo bufferCreateInfo{
			renderer.getDevice(),
			renderer.getVma(),
			indexBuffer.createCreateInfo(size),
			indexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		indexBuffer.create(bufferCreateInfo);
		indexBuffer.fillWithStdContainer(indices);
	}

	void RendererTests::DrawableObject::createUniformBuffers()
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(decltype(mvp))),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.fillWithObject(mvp);
	}

	void RendererTests::DrawableObject::createImageDrawInfos()
	{
		if (!stbImage.load((ContentPath / "texture.jpg").string()))
		{
			FAIL() << "Can't load texture image";
			return;
		}

		Image& image = images.emplace_back();
		Image::CreateInfo imageCreateInfo{
			.device = renderer.getDevice(),
			.vma = renderer.getVma(),
			.vkImageCreateInfo = image.createCreateInfo(stbImage.getWidth(), stbImage.getHeight(), vk::Format::eR8G8B8A8Srgb),
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
		imageBuffer.fillWithCArray(stbImage.get());

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

	void RendererTests::DrawableObject::copyImageBufferToImage(Image& image, ImageBuffer& imageBuffer)
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

	DrawInfo RendererTests::DrawableObject::createDrawInfo()
	{
		DrawInfo drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer };
		drawInfo.indices = indices;
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		drawInfo.uniformBuffers = uniformBuffers;
		drawInfo.images = imageDrawInfos;

		return drawInfo;
	}

	void RendererTests::DrawableObject::rotateImage()
	{
		float time = static_cast<float>(glfwGetTime());
		mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, -1.f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.proj = glm::perspective(glm::radians(45.0f), 800.f / 400.f, 0.1f, 10.0f);
		mvp.proj[1][1] *= -1;

		uniformBuffers[0].fillWithObject(mvp);
	}

	void RendererTests::DrawableObject::rotateImage2()
	{
		float time = -1.f;
		time *= static_cast<float>(glfwGetTime());
		mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 1.f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp.proj = glm::perspective(glm::radians(45.0f), 800.f / 400.f, 0.1f, 10.0f);
		mvp.proj[1][1] *= -1;

		uniformBuffers[0].fillWithObject(mvp);
	}

}