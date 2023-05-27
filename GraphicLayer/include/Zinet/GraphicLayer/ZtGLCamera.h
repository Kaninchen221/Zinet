#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVecTypes.h"

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API Camera
	{

	public:

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

		Matrix4f perspectiveMatrix() const;

	protected:

		Vector3f position;
		Vector3f target;
		Vector3f cameraOrientation;

		float fov;
		float aspect;
		float near;
		float far;

	};

}