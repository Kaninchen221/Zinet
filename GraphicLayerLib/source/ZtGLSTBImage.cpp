#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

namespace zt::gl
{
	STBImage::~STBImage() noexcept
	{
		free();
	}

	bool STBImage::load(const std::string& path)
	{
		data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		
		return !(data == nullptr);
	}

	std::size_t STBImage::sizeBytes() const
	{
		return std::size_t(width) * height * STBI_rgb_alpha;
	}

	void STBImage::free()
	{
		if (data == nullptr)
			return;

		stbi_image_free(data);
		data = nullptr;
		width = 0;
		height = 0;
		channels = 0;
	}
}