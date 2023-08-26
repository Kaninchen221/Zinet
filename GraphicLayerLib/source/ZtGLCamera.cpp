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
		far{ 10.f },
		screenSize{ 1u, 1u },
		type{ Type::Perspective }
	{}

	Matrix4f Camera::viewMatrix() const
	{
		zt::Vector3f tempPosition = position;
		tempPosition.x *= -1.f;
		tempPosition.y *= -1.f;

		return glm::lookAt(tempPosition, target, cameraOrientation);
	}

	Matrix4f Camera::perspectiveMatrix() const
	{
		Matrix4f matrix = glm::perspective(glm::radians(fov), aspect, near, far);
		//matrix[0][0] *= -1.f; // Reversal X axis
		//matrix[1][1] *= -1.f; // Reversal Y axis
		//matrix[2][2] *= -1.f; // Reversal Z axis

		return matrix;
	}

	zt::Matrix4f Camera::orthographicMatrix() const
	{
		float left = static_cast<float>(screenSize.x) / -2.f;
		float right = static_cast<float>(screenSize.x) / 2.f;
		float bottom = static_cast<float>(screenSize.y) / -2.f;
		float top = static_cast<float>(screenSize.y) / 2.f;

		//Matrix4f matrix = glm::ortho(left, right, bottom, top, near, far);
		Matrix4f matrix = glm::ortho(left, right, bottom, top);
		return matrix;
	}

	Matrix4f Camera::projectionMatrix() const
	{
		switch (type)
		{
		case Type::Perspective: return perspectiveMatrix();
		case Type::Ortho: return orthographicMatrix();
		}

		return perspectiveMatrix();
	}

}