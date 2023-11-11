#include "Zinet/GraphicLayer/ZtGLShape2D.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

namespace zt::gl
{
	DrawInfo Shape2D::createDrawInfo(RendererContext& rendererContext) const
	{
		auto defaultIndices = GetDefaultIndices();

		DrawInfo drawInfo;
		drawInfo.indices = std::vector<std::uint16_t>{ defaultIndices.begin(), defaultIndices.end() };
		createVertexBuffer(drawInfo.vertexBuffer, {}, rendererContext);
		createIndexBuffer(drawInfo.indexBuffer, drawInfo.indices, rendererContext);
		createUniformBuffers(drawInfo.uniformBuffers, rendererContext);
		drawInfo.MVPBufferIndex = 0u;

		return drawInfo;
	}

	void Shape2D::createUniformBuffers(std::vector<UniformBuffer>& uniformBuffers, RendererContext& rendererContext) const
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

	std::vector<RenderStates::Descriptor> Shape2D::createRenderStatesDescriptors() const
	{
		std::vector<RenderStates::Descriptor> descriptors;

		// MVP
		RenderStates::Descriptor descriptor;
		descriptor.binding = 0;
		descriptor.descriptorType = vk::DescriptorType::eUniformBuffer;
		descriptor.count = 1;
		descriptor.shaderType = ShaderType::Vertex;
		descriptors.push_back(descriptor);

		return descriptors;
	}

}