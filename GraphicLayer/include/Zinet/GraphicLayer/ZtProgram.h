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
		Program(const Program& Other) = default;
		Program(Program&& Other) = default;

		Program& operator = (const Program& Other) = default;
		Program& operator = (Program&& Other) = default;

		~Program() noexcept;

		void Create();

		void AttachShader(const Shader& Shader) const;

		void Link() const;

		bool LinkStatus() const;

		bool IsValid() const;

		std::string InfoLog() const;

		void Use() const;

		void Delete();

		int GetUniform(const std::string& Name);

		void SetUniform1f(const std::string& Name, float Value);

		void SetUniform2f(const std::string& Name, const glm::vec2& Value);

		void SetUniform3f(const std::string& Name, const glm::vec3& Value);

		void SetUniform4f(const std::string& Name, const glm::vec4& Value);

		void SetUniformMatrix4f(const std::string& Name, const glm::mat4& Value);

		virtual void PrepareAttributes() const;

	};

}