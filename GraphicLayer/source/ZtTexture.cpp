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
	glGenTextures(1, &ID);
}

void ZtTexture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void ZtTexture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ZtTexture::Delete()
{
	glDeleteTextures(1, &ID);
	ID = InvalidID;
}

void ZtTexture::LoadFromData(unsigned char* Data, GLsizei Width, GLsizei Height)
{
	GLint MipmapLevel = 0;
	GLint InternalFormat = GL_RGBA;
	GLint Border = 0;
	GLenum PixelDataFormat = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, MipmapLevel, GL_RGBA, Width, Height, Border, GL_RGB, GL_UNSIGNED_BYTE, Data);
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
	glGenerateMipmap(GL_TEXTURE_2D);
}
