#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Renderer/ZtShaderType.h"

#include <string>

class ZINET_RENDERER_API ZtShader
{
public:

	~ZtShader() noexcept;

	void Create(ZtShaderType ShaderType);

	ZtShaderType GetType() const;

	GLuint GetID() const;

	void LoadFromCString(const char* Source);

	void Compile();

	bool CompileStatus() const;

	std::string CompileErrorMessage() const;

protected:

	ZtShaderType Type;
	GLuint ID;
};