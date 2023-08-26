#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVecTypes.h"

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API Camera
	{

	public:

		enum class Type
		{
			Perspective,
			Ortho
		};

		Camera();
		Camera(const Camera& other) = default;
		Camera(Camera&& other) = default;

		Camera& operator = (const Camera& other) = default;
		Camera& operator = (Camera&& other) = default;

		~Camera() noexcept = default;

		void setPosition(const Vector3f& newPosition) { position = newPosition; }
		const Vector3f& getPosition() const { return position; }

		void setTarget(const Vector3f& newTarget) { target = newTarget; }
		const Vector3f& getTarget() const { return target; }

		void setCameraOrientation(const Vector3f& newCameraOrientation) { cameraOrientation = newCameraOrientation; }
		const Vector3f& getCameraOrientation() const { return cameraOrientation; }

		Matrix4f viewMatrix() const;

		void setFov(float newFov) { fov = newFov; }
		float getFov() const { return fov; }

		void setAspect(float newAspect) { aspect = newAspect; }
		float getAspect() const { return aspect; }

		void setNear(float newNear) { near = newNear; }
		float getNear() const { return near; }

		void setFar(float newFar) { far = newFar; }
		float getFar() const { return far; }

		void setScreenSize(const Vector2ui& newScreenSize) { screenSize = newScreenSize; }
		const Vector2ui& getScreenSize() const { return screenSize; }

		Matrix4f perspectiveMatrix() const;

		Matrix4f orthographicMatrix() const;

		void setType(Type newType) { type = newType; }
		Type getType() const { return type; }

		Matrix4f projectionMatrix() const;

	protected:

		Vector3f position;
		Vector3f target;
		Vector3f cameraOrientation;

		float fov;
		float aspect;
		float near;
		float far;
		Vector2ui screenSize;

		Type type;
	};

}