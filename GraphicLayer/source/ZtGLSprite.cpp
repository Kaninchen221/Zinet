#include "Zinet/GraphicLayer/ZtGLSprite.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	DrawInfo Sprite::createDrawInfo(RendererContext& rendererContext) const
	{
		auto defaultIndices = getDefaultIndices();

		DrawInfo drawInfo;
		drawInfo.indices = std::vector<std::uint16_t>{ defaultIndices.begin(), defaultIndices.end() };
		createVertexBuffer(drawInfo.vertexBuffer, textureRegion, rendererContext);
		createIndexBuffer(drawInfo.indexBuffer, drawInfo.indices, rendererContext);
		createUniformBuffers(drawInfo.uniformBuffers, rendererContext);
		drawInfo.MVPBufferIndex = 0u;

		return std::move(drawInfo);
	}

	void Sprite::setTextureRegion(const TextureRegion& newTextureRegion, const Vector2f& textureSize)
	{
		textureRegion = newTextureRegion.toShaderTextureRegion(textureSize);
	}

	void Sprite::createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const
	{
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

}