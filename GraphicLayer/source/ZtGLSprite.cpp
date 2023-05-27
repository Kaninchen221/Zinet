#include "Zinet/GraphicLayer/ZtGLSprite.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	Sprite::Sprite()
		: drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer }
	{
		drawInfo.modelMatrix = transform.toMatrix();
	}

	const DrawInfo& Sprite::getDrawInfo() const
	{
		return drawInfo;
	}

	void Sprite::createDrawInfo(std::span<Shader> shaders, const Texture& texture, const Sampler& sampler)
	{
		DrawInfo::Image& imageDrawInfo = imageDrawInfos.emplace_back(texture.createImageDrawInfo(sampler));
		imageDrawInfo.binding = 1;

		drawInfo.indices = indices;
		drawInfo.shaders = shaders;
		drawInfo.descriptors = descriptors;
		drawInfo.uniformBuffers = uniformBuffers;
		drawInfo.images = imageDrawInfos;

		Vector2f textureSize = { texture.getImage().getWidth(), texture.getImage().getHeight() };
		TextureRegion shaderTextureRegion = textureRegion.toShaderTextureRegion(textureSize);
		uniformBuffers[1].fillWithObject(shaderTextureRegion);
	}

	void Sprite::create(RendererContext& rendererContext)
	{
		createDescriptors();
		createVertexBuffer(rendererContext);
		createIndexBuffer(rendererContext);
		createUniformBuffers(rendererContext);
	}

	void Sprite::createDescriptors()
	{
		DrawInfo::Descriptor descriptor;
		
		// MVP
		descriptor.binding = 0;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		// TextureRegion
		descriptor.binding = 2;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		// Texture
		descriptor.binding = 1;
		descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Fragment;
		descriptors.push_back(descriptor);
	}

	void Sprite::createVertexBuffer(RendererContext& rendererContext)
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

		vertex.setPosition({ -0.5f, 0.5f, 0.f });
		vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		vertex.setTextureCoordinates({ 1.0f, 1.0f });
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, 0.5f, 0.f });
		vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		vertex.setTextureCoordinates({ 0.0f, 1.0f });
		vertices.push_back(vertex);

		BufferCreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
			rendererContext.getVma(),
			vertexBuffer.createCreateInfo(vertices.size() * sizeof(Vertex)),
			vertexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		vertexBuffer.create(bufferCreateInfo);
		vertexBuffer.fillWithStdContainer(vertices);
	}

	void Sprite::createIndexBuffer(RendererContext& rendererContext)
	{
		indices = { 0, 1, 3, 3, 2, 0 };
		std::uint64_t size = sizeof(decltype(indices)::value_type) * indices.size();

		BufferCreateInfo bufferCreateInfo{
			rendererContext.getDevice(),
			rendererContext.getVma(),
			indexBuffer.createCreateInfo(size),
			indexBuffer.createVmaAllocationCreateInfo(false, true)
		};

		indexBuffer.create(bufferCreateInfo);
		indexBuffer.fillWithStdContainer(indices);
	}

	void Sprite::createUniformBuffers(RendererContext& rendererContext)
	{
		uniformBuffers.reserve(2u);

		createMVPUniformBuffer(rendererContext);
		createTextureRegionUniformBuffer(rendererContext);
	}

	void Sprite::createTextureRegionUniformBuffer(RendererContext& rendererContext)
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(decltype(textureRegion))),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.setBinding(2u);
	}

	UniformBuffer* Sprite::getMVPUniformBuffer()
	{
		if (uniformBuffers.size() < 1)
		{
			Logger->error("Uniform buffers are not created");
			return nullptr;
		}

		return &uniformBuffers[0];
	}

	void Sprite::setTransform(const Transform& newTransform)
	{
		transform = newTransform;
		drawInfo.modelMatrix = transform.toMatrix();
	}

	void Sprite::createMVPUniformBuffer(RendererContext& rendererContext)
	{
		UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
		BufferCreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(MVP)),
			.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
		};
		uniformBuffer.create(bufferCreateInfo);
		uniformBuffer.setBinding(0u);
	}

	void Sprite::copyFrom(const Sprite& other, RendererContext& rendererContext)
	{
		create(rendererContext);
		transform = other.getTransform();
		textureRegion = other.getTextureRegion();
	}

}