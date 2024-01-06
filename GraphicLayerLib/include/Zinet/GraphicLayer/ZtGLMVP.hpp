#pragma once

#include "ZtGraphicLayerConfig.hpp"

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API MVP
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

}