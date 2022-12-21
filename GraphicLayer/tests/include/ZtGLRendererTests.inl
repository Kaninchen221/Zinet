#include "ZtGLRendererTests.h"

namespace zt::gl::tests
{

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

	inline void RendererTests::createDescriptors()
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

	inline void RendererTests::createVertexBuffer()
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

	inline void RendererTests::createIndexBuffer()
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

	inline void RendererTests::createUniformBuffers()
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

	inline void RendererTests::createImageDrawInfos()
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