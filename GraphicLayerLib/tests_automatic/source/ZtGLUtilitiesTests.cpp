#pragma once

#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"

#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl::tests
{

	class UtilitiesTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		RendererContext rendererContext;
		Texture texture;
		STBImage stbImage;

		void SetUp() override
		{
			wd::GLFW::Init();

			rendererContext.initialize();
			createSTBImage();
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}

		void createSTBImage();
	};

	void UtilitiesTests::createSTBImage()
	{
		if (!stbImage.load((ContentPath / "test_texture.png").string()))
		{
			FAIL() << "Can't load texture image";
		}
	}

	TEST_F(UtilitiesTests, FromExtent2DToVector2)
	{
		vk::Extent2D extent{ 234u, 1111u }; //std::uint32_t
		Vector2ui expected{ extent.width, extent.height };
		Vector2ui actual = Utilities::FromExtent2DToVector2<Vector2ui>(extent);
		EXPECT_EQ(expected, actual);
	}

	TEST_F(UtilitiesTests, FromVector2Extent2DTo)
	{
		Vector2ui vector{ 123132u, 212u };
		vk::Extent2D expected{ vector.x, vector.y }; //std::uint32_t
		vk::Extent2D actual = Utilities::FromVector2ToExtent2D(vector);
		EXPECT_EQ(expected, actual);
	}
}
