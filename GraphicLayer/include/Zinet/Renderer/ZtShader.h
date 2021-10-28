#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Renderer/ZtShaderType.h"
#include "Zinet/Renderer/ZtObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <string>

class ZINET_RENDERER_API ZtShader : public ZtObject
{
	static inline ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtShader");

public:

	ZtShader() = default;
	ZtShader(const ZtShader& Other) = default;
	ZtShader(ZtShader&& Other) = default;

	ZtShader& operator = (const ZtShader& Other) = default;
	ZtShader& operator = (ZtShader&& Other) = default;

	~ZtShader() noexcept;

	void Create(ZtShaderType ShaderType);

	void Delete();

	ZtShaderType GetType() const;

	void LoadFromCString(const char* Source);

	void LoadFromFile(const std::string& Path);

	void Compile();

	bool CompileStatus() const;

	std::string CompileErrorMessage() const;

protected:

	ZtShaderType Type{};
};