#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include "Zinet/Core/ZtFileFinder.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Texture : public Object
	{

	public:

		Texture() = default;
		Texture(const Texture& Other) = default;
		Texture(Texture&& Other) = default;

		Texture& operator = (const Texture& Other) = default;
		Texture& operator = (Texture&& Other) = default;

		~Texture() noexcept;

		void Generate();

		void Bind() const;

		void Unbind() const;

		void Delete();

		void LoadFromData(unsigned char* Data, GLsizei Width, GLsizei Height);

		void LoadFromFile(const FileFinder::Path& Path);

		void GenerateMipmap() const;

	};

}