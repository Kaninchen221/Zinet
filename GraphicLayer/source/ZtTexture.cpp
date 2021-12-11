#include "Zinet/GraphicLayer/ZtTexture.h"

#include "stb_image.h"

namespace zt::gl
{

	Texture::~Texture() noexcept
	{
		if (ID != InvalidID)
		{
			Delete();
		}
	}

	void Texture::Generate()
	{

	}

	void Texture::Bind() const
	{

	}

	void Texture::Unbind() const
	{

	}

	void Texture::Delete()
	{
		ID = InvalidID;
	}

	void Texture::LoadFromData(unsigned char* Data, GLsizei Width, GLsizei Height)
	{

	}

	void Texture::LoadFromFile(const FileFinder::Path& Path)
	{
		std::string PathString = Path.string();
		const char* PathCString = PathString.c_str();

		int TextureWidth;
		int TextureHeight;
		int ChannelsNumber;
		unsigned char* TextureData = stbi_load(PathCString, &TextureWidth, &TextureHeight, &ChannelsNumber, 0);

		LoadFromData(TextureData, TextureWidth, TextureHeight);
		stbi_image_free(TextureData);
	}

	void Texture::GenerateMipmap() const
	{

	}

}