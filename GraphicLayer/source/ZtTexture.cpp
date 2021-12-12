#include "Zinet/GraphicLayer/ZtTexture.h"

#include "stb_image.h"

namespace zt::gl
{

	Texture::~Texture() noexcept
	{
		if (iD != InvalidID)
		{
			deleteResource();
		}
	}

	void Texture::generate()
	{

	}

	void Texture::bind() const
	{

	}

	void Texture::unbind() const
	{

	}

	void Texture::deleteResource()
	{
		iD = InvalidID;
	}

	void Texture::loadFromData(unsigned char* data, GLsizei width, GLsizei height)
	{

	}

	void Texture::loadFromFile(const FileFinder::Path& path)
	{
		std::string pathString = path.string();
		const char* pathCString = pathString.c_str();

		int textureWidth;
		int textureHeight;
		int channelsNumber;
		unsigned char* textureData = stbi_load(pathCString, &textureWidth, &textureHeight, &channelsNumber, 0);

		loadFromData(textureData, textureWidth, textureHeight);
		stbi_image_free(textureData);
	}

	void Texture::generateMipmap() const
	{

	}

}