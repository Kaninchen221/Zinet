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
	}

	void Sprite::create(RendererContext& rendererContext, const Vector2f& textureSize)
	{
		createDescriptors();
		createVertexBuffer(rendererContext, textureSize);
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

		// Texture
		descriptor.binding = 1;
		descriptor.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Fragment;
		descriptors.push_back(descriptor);
	}

	void Sprite::createVertexBuffer(RendererContext& rendererContext, const Vector2f& textureSize)
	{
		TextureRegion shaderTextureRegion = textureRegion.toShaderTextureRegion(textureSize);
		Vector2f UV = shaderTextureRegion.offset;

		Vertex vertex;
		vertex.setPosition({ -0.5f, 0.5f, 0.f });
		vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, 0.5f, 0.f });
		vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		UV.x += shaderTextureRegion.size.x;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, -0.5f, 0.f });
		vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		UV = shaderTextureRegion.offset;
		UV += shaderTextureRegion.size;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ -0.5f, -0.5f, 0.f });
		vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		UV = shaderTextureRegion.offset;
		UV.y += shaderTextureRegion.size.y;
		vertex.setTextureCoordinates(UV);
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
		indices = { 0, 1, 2, 2, 3, 0 };
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
		create(rendererContext, {}); // TODO Fix this
		transform = other.getTransform();
		textureRegion = other.getTextureRegion();
	}

}