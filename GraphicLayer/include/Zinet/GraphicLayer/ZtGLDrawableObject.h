#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLDrawInfo.h"
#include "Zinet/GraphicLayer/ZtGLTransform.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Texture;
	class Sampler;

	class ZINET_GRAPHIC_LAYER_API DrawableObject
	{

	public:

		DrawableObject() = default;
		DrawableObject(const DrawableObject& other) = default;
		DrawableObject(DrawableObject&& other) = default;

		DrawableObject& operator = (const DrawableObject& other) = default;
		DrawableObject& operator = (DrawableObject&& other) = default;

		virtual ~DrawableObject() noexcept = default;

		virtual const DrawInfo& getDrawInfo() const = 0;

		virtual void createDrawInfo(std::span<Shader> shaders, const Texture& texture, const Sampler& sampler) = 0;

		virtual const Transform& getTransform() const = 0;

		virtual UniformBuffer* getMVPUniformBuffer() = 0;
	};

}