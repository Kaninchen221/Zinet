#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Renderer/ZtShaderType.h"

#include "Zinet/Core/ZtLogger.h"

#include <string>

class ZINET_RENDERER_API ZtShader
{
	static inline ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtShader");

public:

	~ZtShader() noexcept;

	void Create(ZtShaderType ShaderType);

	ZtShaderType GetType() const;

	GLuint GetID() const;

	void LoadFromCString(const char* Source);

	void LoadFromFile(const std::string& Path);

	void Compile();

	bool CompileStatus() const;

	std::string CompileErrorMessage() const;

protected:

	ZtShaderType Type;
	GLuint ID;
};