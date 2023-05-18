#include "Zinet/GraphicLayer/ZtGLCamera.h"

namespace zt::gl
{

	Camera::Camera()
		: position{ 0.f, 0.f, 10.f },
		target{ 0.f, 0.f, 0.f },
		cameraOrientation{ 0.f, 0.f, 1.f },
		fov{ 45.f },
		aspect{ 800.f / 400.f },
		near{ 0.1f },
		far{ 10.f }
	{}

	Matrix4f Camera::viewMatrix() const
	{
		return glm::lookAt(position, target, cameraOrientation);
	}

	Matrix4f Camera::projectionMatrix() const
	{
		Matrix4f matrix;
		matrix = glm::perspective(glm::radians(fov), aspect, near, far);
		matrix[1][1] *= -1; // Reversal Y axis

		return matrix;
	}

}