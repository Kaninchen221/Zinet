#include "Zinet/GraphicLayer/ZtGLFlipbook.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	DrawInfo Flipbook::createDrawInfo(RendererContext& rendererContext) const
	{
		auto defaultIndices = getDefaultIndices();

		DrawInfo drawInfo;
		drawInfo.indices = std::vector<std::uint16_t>{ defaultIndices.begin(), defaultIndices.end() };

		createVertexBuffer(drawInfo.vertexBuffer, TextureRegion{}, rendererContext);
		createIndexBuffer(drawInfo.indexBuffer, drawInfo.indices, rendererContext);
		createUniformBuffers(drawInfo.uniformBuffers, rendererContext);
		createStorageBuffers(drawInfo.storageBuffers, rendererContext);
		drawInfo.MVPBufferIndex = 0u;

		return std::move(drawInfo);
	}

	void Flipbook::createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const
	{
		uniformBuffers.reserve(2u);

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

	void Flipbook::createStorageBuffers(std::vector<StorageBuffer>& storageBuffers, RendererContext& rendererContext) const
	{
		StorageBuffer& storageBuffer = storageBuffers.emplace_back();
		Buffer::CreateInfo bufferCreateInfo{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkBufferCreateInfo = storageBuffer.createCreateInfo(sizeof(Vector2f) * 4u),
			.allocationCreateInfo = storageBuffer.createVmaAllocationCreateInfo(false, false)
		};
		storageBuffer.create(bufferCreateInfo);
		storageBuffer.setBinding(2u);

		if (!frames.empty())
		{
			const Frame& frame = frames[currentFrameIndex];
			const TextureRegion& textureRegion = frame.shaderTextureRegion;
			std::array<Vector2f, 4u> uv =
			{
				textureRegion.offset,
				Vector2f{ textureRegion.offset.x + textureRegion.size.x, textureRegion.offset.y },
				textureRegion.offset + textureRegion.size,
				Vector2f{ textureRegion.offset.x, textureRegion.offset.y + textureRegion.size.y },
			};
			storageBuffer.fillWithStdContainer(uv);
		}
	}

	void Flipbook::play()
	{
		currentState = State::Playing;
	}

	void Flipbook::pause()
	{
		currentState = State::Pause;
	}

	bool Flipbook::update(const zt::core::Time& currentTime)
	{
		if (currentState == State::Pause)
			return false;

		if (frames.empty())
			return false;

		const Frame& currentFrame = frames[currentFrameIndex];
		zt::core::Time timeElapsed = currentTime - lastTimeUpdated;
		if (timeElapsed >= currentFrame.time)
		{
			lastTimeUpdated = currentTime;
			size_t nextFrameIndex = ++currentFrameIndex;
			if (nextFrameIndex >= frames.size())
				nextFrameIndex = 0u;

			currentFrameIndex = nextFrameIndex;

			return true;
		}

		return false;
	}

}