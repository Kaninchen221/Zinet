#include "Zinet/GraphicLayer/ZtGLTransform.h"

namespace zt::gl
{

	Matrix4f Transform::toMatrix() const
	{
		glm::mat4 result = glm::mat4(1.0f);
		result = glm::scale(result, glm::vec3(scale));
		result = glm::rotate(result, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		result = glm::rotate(result, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		result = glm::rotate(result, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		result = glm::translate(result, glm::vec3(translation));

		return result;
	}

}