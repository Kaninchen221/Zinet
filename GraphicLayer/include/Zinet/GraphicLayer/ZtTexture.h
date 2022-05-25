#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtObject.h"

#include "Zinet/Core/ZtFileFinder.h"

namespace zt::gl
{

	// TODO Remove that class
	class ZINET_GRAPHIC_LAYER_API Texture : public Object
	{

	public:

		Texture() = default;
		Texture(const Texture& other) = default;
		Texture(Texture&& other) = default;

		Texture& operator = (const Texture& other) = default;
		Texture& operator = (Texture&& other) = default;

		~Texture() noexcept;

		void generate();

		void bind() const;

		void unbind() const;

		void deleteResource();

		void loadFromData(unsigned char* data, GLsizei width, GLsizei height);

		void loadFromFile(const FileFinder::Path& path);

		void generateMipmap() const;

	};

}