#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Window/ZtVecTypes.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API STBImage
	{

	public:

		using MemoryPointer = stbi_uc;

		STBImage() = default;
		STBImage(const STBImage& other) = default;
		STBImage(STBImage&& other) = default;

		STBImage& operator = (const STBImage& other) = default;
		STBImage& operator = (STBImage&& other) = default;

		~STBImage() noexcept;

		MemoryPointer* get() { return data; }
		const MemoryPointer* get() const { return data; }

		bool load(const std::string& path);

		int getWidth() const { return width; }

		int getHeight() const { return height; }

		Vector2ui getSize() const { return Vector2ui{ width, height }; }

		int getChannels() const { return channels; }

		std::size_t sizeBytes() const;

		void free();

	protected:

		MemoryPointer* data = nullptr;
		int width = 0;
		int height = 0;
		int channels = 0;
	};

}