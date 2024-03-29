#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Math/ZtVecTypes.hpp"

#include "Zinet/Core/ZtLogger.hpp"

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

		void setRotation(const Vector3f& newRotation) { rotation = newRotation; }
		const Vector3f& getRotation() const { return rotation; }

		void setTranslation(const Vector3f& newTranslation) { translation = newTranslation; }
		const Vector3f& getTranslation() const { return translation; }

		void setScale(const Vector3f& newScale) { scale = newScale; }
		const Vector3f& getScale() const { return scale; }

		Matrix4f toMatrix() const;

		void combine(const Transform& other);

	protected:

		Vector3f rotation = { 0.f, 0.f, 0.f }; // In degrees
		Vector3f translation = { 0.f, 0.f, 0.f };
		Vector3f scale = { 1.f, 1.f, 1.f };

	};

	inline bool operator == (const Transform& first, const Transform& second)
	{
		bool isRotationEqual = first.getRotation() == second.getRotation();
		bool isScaleEqual = first.getScale() == second.getScale();
		bool isTranslationEqual = first.getTranslation() == second.getTranslation();

		return isRotationEqual && isScaleEqual && isTranslationEqual;
	}

}