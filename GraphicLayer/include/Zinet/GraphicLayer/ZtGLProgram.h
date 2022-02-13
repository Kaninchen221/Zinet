#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

namespace zt::gl
{
	class Shader;

	class ZINET_GRAPHIC_LAYER_API Program
	{
		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Program");

	public:

		Program() = default;
		Program(const Program& other) = default;
		Program(Program&& other) = default;

		Program& operator = (const Program& other) = default;
		Program& operator = (Program&& other) = default;

		~Program() noexcept = default;

		void attachShader(Shader& shader);

		bool link();

	protected:


	};

}