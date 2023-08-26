#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Window/ZtVecTypes.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API Transform
	{

	public:

		Transform() = default;
		Transform(const Transform& other) = default;
		Transform(Transform&& other) = default;

		Transform& operator = (const Transform& other) = default;
		Transform& operator = (Transform&& other) = default;

		~Transform() noexcept = default;

		void setRotation(const zt::Vector3f& newRotation) { rotation = newRotation; }
		const zt::Vector3f& getRotation() const { return rotation; }

		void setTranslation(const zt::Vector3f& newTranslation) { translation = newTranslation; }
		const zt::Vector3f& getTranslation() const { return translation; }

		void setScale(const zt::Vector3f& newScale) { scale = newScale; }
		const zt::Vector3f& getScale() const { return scale; }

		Matrix4f toMatrix() const;

		void combine(const Transform& other);

	protected:

		zt::Vector3f rotation = { 0.f, 0.f, 0.f }; // In degrees
		zt::Vector3f translation = { 0.f, 0.f, 0.f };
		zt::Vector3f scale = { 1.f, 1.f, 1.f };

	};

	inline bool operator == (const Transform& first, const Transform& second)
	{
		bool isRotationEqual = first.getRotation() == second.getRotation();
		bool isScaleEqual = first.getScale() == second.getScale();
		bool isTranslationEqual = first.getTranslation() == second.getTranslation();

		return isRotationEqual && isScaleEqual && isTranslationEqual;
	}

}