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

		TextureRegion textureRegion = frames[currentFrameIndex].shaderTextureRegion;
		createVertexBuffer(drawInfo.vertexBuffer, textureRegion, rendererContext);
		createIndexBuffer(drawInfo.indexBuffer, drawInfo.indices, rendererContext);
		createUniformBuffers(drawInfo.uniformBuffers, rendererContext);
		drawInfo.MVPBufferIndex = 0u;

		return std::move(drawInfo);
	}

	void Flipbook::createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const
	{
		uniformBuffers.reserve(2u);

		{ // Mvp buffer
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

		{ // TextureRegion
			UniformBuffer& uniformBuffer = uniformBuffers.emplace_back();
			Buffer::CreateInfo bufferCreateInfo{
				.device = rendererContext.getDevice(),
				.vma = rendererContext.getVma(),
				.vkBufferCreateInfo = uniformBuffer.createCreateInfo(sizeof(TextureRegion)),
				.allocationCreateInfo = uniformBuffer.createVmaAllocationCreateInfo(false, true)
			};
			uniformBuffer.create(bufferCreateInfo);
			uniformBuffer.setBinding(2u);

			if (!frames.empty())
				uniformBuffer.fillWithObject(frames[currentFrameIndex].shaderTextureRegion);
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