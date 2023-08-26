#pragma once

#include "Zinet/GraphicLayer/ZtGLUtilities.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTexture.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

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
			GLFW::Init();

			rendererContext.initialize();
			createSTBImage();
		}

		void TearDown() override
		{
			GLFW::Deinit();
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
}
