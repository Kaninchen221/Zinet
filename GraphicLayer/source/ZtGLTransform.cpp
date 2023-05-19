#include "Zinet/GraphicLayer/ZtGLTransform.h"

#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_inverse.hpp>

namespace zt::gl
{
	// TODO The order of s r t is wrong
	Matrix4f Transform::toMatrix() const
	{
		glm::mat4 result = glm::mat4(1.0f);
		result = glm::scale(result, scale);
		result = glm::rotate(result, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		result = glm::rotate(result, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		result = glm::rotate(result, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		result = glm::translate(result, translation);

		return result;
	}

	void Transform::combine(const Transform& other)
	{
		rotation += other.getRotation();
		scale *= other.getScale();
		translation += other.getTranslation();
	}

}