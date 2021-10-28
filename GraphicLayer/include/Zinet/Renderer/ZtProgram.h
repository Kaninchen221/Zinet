#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Renderer/ZtShader.h"
#include "Zinet/Renderer/ZtObject.h"

#include "glad/glad.h"

class ZINET_RENDERER_API ZtProgram : public ZtObject
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

};