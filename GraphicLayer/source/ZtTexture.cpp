#include "Zinet/GraphicLayer/ZtTexture.h"

#include "stb_image.h"

ZtTexture::~ZtTexture() noexcept
{
	if (ID != InvalidID)
	{
		Delete();
	}
}

void ZtTexture::Generate()
{

}

void ZtTexture::Bind() const
{

}

void ZtTexture::Unbind() const
{

}

void ZtTexture::Delete()
{
	ID = InvalidID;
}

void ZtTexture::LoadFromData(unsigned char* Data, GLsizei Width, GLsizei Height)
{

}

void ZtTexture::LoadFromFile(const ZtFileFinder::Path& Path)
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

void ZtTexture::GenerateMipmap() const
{

}
