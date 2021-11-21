#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtShader.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4x4.hpp"

#include "glad/glad.h"

class ZINET_GRAPHIC_LAYER_API ZtProgram : public ZtObject
{

public:

	ZtProgram() = default;
	ZtProgram(const ZtProgram& Other) = default;
	ZtProgram(ZtProgram&& Other) = default;

	ZtProgram& operator = (const ZtProgram& Other) = default;
	ZtProgram& operator = (ZtProgram&& Other) = default;

	~ZtProgram() noexcept;

	void Create();

	void AttachShader(const ZtShader& Shader) const;

	void Link() const;

	bool LinkStatus() const;

	bool IsValid() const;

	std::string InfoLog() const;

	void Use() const;

	void Delete();

	GLint GetUniform(const std::string& Name);

	void SetUniform1f(const std::string& Name, float Value);

	void SetUniform2f(const std::string& Name, const glm::vec2& Value);

	void SetUniform3f(const std::string& Name, const glm::vec3& Value);

	void SetUniform4f(const std::string& Name, const glm::vec4& Value);

	void SetUniformMatrix4f(const std::string& Name, const glm::mat4& Value);

};