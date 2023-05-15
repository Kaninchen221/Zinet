#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLVecTypes.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	// TODO Use quaternion for rotation
	class ZINET_GRAPHIC_LAYER_API Transform
	{

	public:

		Transform() = default;
		Transform(const Transform& other) = default;
		Transform(Transform&& other) = default;

		Transform& operator = (const Transform& other) = default;
		Transform& operator = (Transform&& other) = default;

		~Transform() noexcept = default;

		void setRotation(const Vector4f& newRotation) { rotation = newRotation; }
		const Vector4f& getRotation() const { return rotation; }

		void setTranslation(const Vector4f& newTranslation) { translation = newTranslation; }
		const Vector4f& getTranslation() const { return translation; }

		void setScale(const Vector4f& newScale) { scale = newScale; }
		const Vector4f& getScale() const { return scale; }

		Matrix4f toMatrix() const;

	protected:

		// TODO This properties should be perhaps Vector3f
		Vector4f rotation = { 0.f, 0.f, 0.f, 1.f }; // In degrees
		Vector4f translation = { 0.f, 0.f, 0.f, 0.f };
		Vector4f scale = { 1.f, 1.f, 1.f, 0.f };

	};

}