#include "Zinet/GraphicLayer/ZtGLSprite.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	Sprite::Sprite()
	{
	}

	DrawInfo Sprite::createDrawInfo(RendererContext& rendererContext) const
	{
		DrawInfo drawInfo;
		drawInfo.indices = getIndices();
		createVertexBuffer(drawInfo.vertexBuffer, rendererContext);
		createIndexBuffer(drawInfo.indexBuffer, rendererContext);
		createUniformBuffers(drawInfo.uniformBuffers, rendererContext);
		drawInfo.MVPBufferIndex = 0u;

		return std::move(drawInfo);
	}

	void Sprite::createVertexBuffer(VertexBuffer& vertexBuffer, RendererContext& rendererContext) const
	{
		Vector2f UV = textureRegion.offset;

		std::vector<Vertex> vertices;
		Vertex vertex;
		vertex.setPosition({ -0.5f, 0.5f, 0.f });
		vertex.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, 0.5f, 0.f });
		vertex.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
		UV.x += textureRegion.size.x;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ 0.5f, -0.5f, 0.f });
		vertex.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		UV = textureRegion.offset;
		UV += textureRegion.size;
		vertex.setTextureCoordinates(UV);
		vertices.push_back(vertex);

		vertex.setPosition({ -0.5f, -0.5f, 0.f });
		vertex.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		UV = textureRegion.offset;
		UV.y += textureRegion.size.y;
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

	void Sprite::createIndexBuffer(IndexBuffer& indexBuffer, RendererContext& rendererContext) const
	{
		std::vector<std::uint16_t> indices = getIndices();
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

	void Sprite::setTransform(const Transform& newTransform)
	{
		transform = newTransform;
	}

	void Sprite::setTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize)
	{
		textureRegion = newTextureRegion.toShaderTextureRegion(textureSize);
	}

	void Sprite::createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const
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

	std::vector<std::uint16_t> Sprite::getIndices() const
	{
		return { 0, 1, 2, 2, 3, 0 };
	}

}