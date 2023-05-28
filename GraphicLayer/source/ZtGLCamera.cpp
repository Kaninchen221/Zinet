#include "Zinet/GraphicLayer/ZtGLCamera.h"

namespace zt::gl
{

	Camera::Camera()
		: position{ 0.f, 0.f, 5.f },
		target{ 0.f, 0.f, 0.f },
		cameraOrientation{ 0.f, -1.f, 0.f },
		fov{ 45.f },
		aspect{ 800.f / 400.f },
		near{ 0.01f },
		far{ 10.f }
	{}

	Matrix4f Camera::viewMatrix() const
	{
		Vector3f tempTarget = target;// *-1.f;

		Vector3f tempPosition = position;
		tempPosition.x *= -1.f;
		tempPosition.y *= -1.f;

		return glm::lookAt(tempPosition, tempTarget, cameraOrientation);
	}

	Matrix4f Camera::perspectiveMatrix() const
	{
		Matrix4f matrix;
		matrix = glm::perspective(glm::radians(fov), aspect, near, far);
		//matrix[0][0] *= -1.f; // Reversal X axis
		//matrix[1][1] *= -1.f; // Reversal Y axis
		//matrix[2][2] *= -1.f; // Reversal Z axis

		return matrix;
	}

}