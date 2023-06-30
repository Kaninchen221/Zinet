#pragma once

#include "Zinet/GraphicLayer/ZtGLVecTypes.h"

namespace zt::gl
{
	class ZINET_GRAPHIC_LAYER_API Math
	{
	public:

		Math() = delete;
		Math(const Math& other) = delete;
		Math(Math&& other) = delete;

		Math& operator = (const Math& other) = delete;
		Math& operator = (Math&& other) = delete;

		~Math() noexcept = delete;

		static Vector3f FromCArrayToVector3f(float array[3])
		{
			Vector3f result;
			result.x = array[0];
			result.y = array[1];
			result.z = array[2];

			return result;
		}

		static void FromVector3fToCArray(const Vector3f& vector, float array[3])
		{
			array[0] = vector.x;
			array[1] = vector.y;
			array[2] = vector.z;
		}
	};
}