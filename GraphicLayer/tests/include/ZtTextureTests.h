#pragma once

#include "Zinet/GraphicLayer/ZtTexture.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtTextureTests : public ::testing::Test
	{
	protected:

		ZtTextureTests()
		{
			window.createWindow();
		}

		~ZtTextureTests()
		{
			texture.deleteResource();
		}

		Texture texture;
		Window window;

	};

	TEST_F(ZtTextureTests, GenerateTest)
	{
		texture.generate();
		GLuint actualID = texture.getID();
		GLuint notExpectedID = Texture::InvalidID;
	}

	TEST_F(ZtTextureTests, GetIDTest)
	{
		GLuint ID = texture.getID();
	}

	TEST_F(ZtTextureTests, BindTest)
	{
		texture.generate();
		texture.bind();
		GLint actualBindedTexture2D = 0;
	}

	TEST_F(ZtTextureTests, UnbindTest)
	{
		texture.generate();
		texture.bind();
		texture.unbind();

		GLint actualBindedTexture2D = 0;
	}

	TEST_F(ZtTextureTests, DeleteTest)
	{
		texture.generate();
		texture.bind();
		GLuint previousID = texture.getID();
		texture.deleteResource();

		GLuint actualID = texture.getID();
		GLuint expectedID = Texture::InvalidID;

		ASSERT_EQ(actualID, expectedID);
	}

	TEST_F(ZtTextureTests, LoadFromDataTest)
	{
		texture.generate();
		texture.bind();

		unsigned char* data = nullptr;
		GLsizei width{};
		GLsizei height{};
		texture.loadFromData(data, width, height);
	}

	TEST_F(ZtTextureTests, LoadFromFileTest)
	{
		texture.generate();
		texture.bind();

		zt::FileFinder fileFinder;
		zt::FileFinder::Path rootPath = fileFinder.currentProjectRootPath();
		zt::FileFinder::Path filePath = rootPath / "Textures" / "wall.jpg";
		texture.loadFromFile(filePath);
	}

	TEST_F(ZtTextureTests, GenerateMipmapTest)
	{
		texture.generateMipmap();
	}

}