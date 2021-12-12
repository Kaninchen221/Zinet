#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtShader.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Program : public Object
	{

	public:

		Program() = default;
		Program(const Program& other) = default;
		Program(Program&& other) = default;

		Program& operator = (const Program& other) = default;
		Program& operator = (Program&& other) = default;

		~Program() noexcept;

		void create();

		void attachShader(const Shader& shader) const;

		void link() const;

		bool linkStatus() const;

		bool isValid() const;

		std::string infoLog() const;

		void use() const;

		void deleteResource();

		int getUniform(const std::string& name);

		void setUniform1f(const std::string& name, float value);

		void setUniform2f(const std::string& name, const glm::vec2& value);

		void setUniform3f(const std::string& name, const glm::vec3& value);

		void setUniform4f(const std::string& name, const glm::vec4& value);

		void setUniformMatrix4f(const std::string& name, const glm::mat4& value);

		virtual void prepareAttributes() const;

	};

}