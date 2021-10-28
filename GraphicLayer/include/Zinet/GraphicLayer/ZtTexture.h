#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include "Zinet/Core/ZtFileFinder.h"

class ZINET_GRAPHIC_LAYER_API ZtTexture : public ZtObject
{

public:

	ZtTexture() = default;
	ZtTexture(const ZtTexture & Other) = default;
	ZtTexture(ZtTexture && Other) = default;

	ZtTexture& operator = (const ZtTexture & Other) = default;
	ZtTexture& operator = (ZtTexture && Other) = default;

	~ZtTexture() noexcept;

	void Generate();

	void Bind() const;

	void Unbind() const;

	void Delete();

	void LoadFromData(unsigned char* Data, GLsizei Width, GLsizei Height);

	void LoadFromFile(const ZtFileFinder::Path& Path);

	void GenerateMipmap() const;

};