#pragma once

#include "Zinet/GraphicLayer/ZtGLSTBImage.h"

#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class STBImageTests : public ::testing::Test
	{
	protected:

		STBImage image;

		std::string texturePath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/texture.jpg";
	};

	TEST_F(STBImageTests, Get)
	{
		STBImage::MemoryPointer* pointer = image.get();

		ASSERT_EQ(pointer, nullptr);
	}

	TEST_F(STBImageTests, GetWidth)
	{
		int width = image.getWidth();

		ASSERT_EQ(width, 0);
	}

	TEST_F(STBImageTests, GetHeight)
	{
		int height = image.getHeight();

		ASSERT_EQ(height, 0);
	}

	TEST_F(STBImageTests, GetSize)
	{
		Vector2ui size = image.getSize();

		ASSERT_EQ(size.x, image.getWidth());
		ASSERT_EQ(size.y, image.getHeight());
	}

	TEST_F(STBImageTests, GetChannels)
	{
		int channels = image.getChannels();

		ASSERT_EQ(channels, 0);
	}

	TEST_F(STBImageTests, Load)
	{
		bool result = image.load(texturePath);
		ASSERT_TRUE(result);

		STBImage::MemoryPointer* pointer = image.get();
		ASSERT_NE(pointer, nullptr);

		int width = image.getWidth();
		ASSERT_EQ(width, 512);

		int height = image.getHeight();
		ASSERT_EQ(height, 512);

		int channels = image.getChannels();
		ASSERT_EQ(channels, 3);
	}

	TEST_F(STBImageTests, SizeInMemory)
	{
		bool result = image.load(texturePath);
		ASSERT_TRUE(result);

		std::size_t size = image.sizeBytes();
		ASSERT_EQ(size, 1048576);
	}

	TEST_F(STBImageTests, Free)
	{
		[[maybe_unused]] bool result = image.load(texturePath);
		image.free();

		STBImage::MemoryPointer* pointer = image.get();
		ASSERT_EQ(pointer, nullptr);

		int width = image.getWidth();
		ASSERT_EQ(width, 0);

		int height = image.getHeight();
		ASSERT_EQ(height, 0);

		int channels = image.getChannels();
		ASSERT_EQ(channels, 0);
	}
}
