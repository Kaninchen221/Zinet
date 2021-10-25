#pragma once

#include "Zinet/Renderer/ZtRenderer.h"
#include "Zinet/Core/ZtFileFinder.h"

class ZINET_RENDERER_API ZtTexture
{

public:

	const inline static GLuint InvalidID = 0u;

	ZtTexture() = default;
	ZtTexture(const ZtTexture & Other) = default;
	ZtTexture(ZtTexture && Other) = default;

	ZtTexture& operator = (const ZtTexture & Other) = default;
	ZtTexture& operator = (ZtTexture && Other) = default;

	~ZtTexture() noexcept;

	void Generate();

	GLuint GetID() const;

	void Bind() const;

	void Unbind() const;

	void Delete();

	void LoadFromData(unsigned char* Data, GLsizei Width, GLsizei Height);

	void LoadFromFile(const ZtFileFinder::Path& Path);

	void GenerateMipmap() const;

protected:

	GLuint ID = 0u;

};