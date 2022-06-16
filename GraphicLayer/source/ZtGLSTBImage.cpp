#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

namespace zt::gl
{
	STBImage::~STBImage() noexcept
	{
		stbi_image_free(data);
	}

	STBImage::MemoryPointer* STBImage::get()
	{
		return data;
	}

	bool STBImage::load(const std::string& path)
	{
		data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		
		return !(data == nullptr);
	}

	int STBImage::getWidth() const
	{
		return width;
	}

	int STBImage::getHeight() const
	{
		return height;
	}

	int STBImage::getChannels() const
	{
		return channels;
	}

	void STBImage::free()
	{
		stbi_image_free(data);
		data = nullptr;
		width = 0;
		height = 0;
		channels = 0;
	}
}