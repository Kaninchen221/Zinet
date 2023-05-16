#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>

namespace zt::gl
{
	using Vector2f = glm::vec2;
	using Vector2d = glm::vec<2, double, glm::defaultp>;
	using Vector2i = glm::vec<2, int, glm::defaultp>;
	using Vector2ui = glm::vec<2, unsigned int, glm::defaultp>;

	using Vector3f = glm::vec3;

	using Vector4f = glm::vec4;

	using Matrix4f = glm::mat4;
}